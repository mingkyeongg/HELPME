/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_delimited.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:32:15 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/04 21:16:50 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void process_prev_str(char *token, int start, int index, t_comm **cmd)
{
	char *new_token;

	new_token = mk_strdup(start, index - 1, token, REMOVE);
	process_env_var(&new_token, cmd, UNQUOTED, token);
    push_back(cmd, new_token, STR);
    free(new_token);
}

void distinguishing_redirec(char *new_token, int flag, t_comm **cmd)
{
	if (ft_strchr(new_token, '<') && flag == SINGLE)
		push_back(cmd, new_token, LESS);
	else if (ft_strchr(new_token, '>')  && flag == SINGLE)
		push_back(cmd, new_token, GREAT);
	else if (ft_strchr(new_token, '<') && flag == DOUBLE)
		push_back(cmd, new_token, DLESS);
	else if (ft_strchr(new_token, '>')  && flag == DOUBLE)
		push_back(cmd, new_token, DGREAT);
}

void push_back_delimited(char *token, int *index, t_comm **cmd, int *start)
{
	char *new_token;

	new_token = NULL;
	if (token[*index] == '|')
	{
		new_token = mk_strdup(*index, *index, token, REMOVE);
		push_back(cmd, new_token, PIPE);
		*index += 1;
	}
    else if ((token[*index] == '<' || token[*index] == '>') && token[*index + 1] == token[*index])
    {
        new_token = mk_strdup(*index, *index + 1, token, REMOVE);
		distinguishing_redirec(new_token, DOUBLE, cmd);
        *index += 2;
    }
    else
    {
    	new_token = mk_strdup(*index, *index, token, REMOVE);
		distinguishing_redirec(new_token, SINGLE, cmd);
		*index += 1;
    }
    free(new_token);
	*start = *index;
}

char *find_delimited(char *token, t_comm **cmd, int i, int start)
{
    char *new_token;

	while(is_space(token[i]))
	{
		i++;
		start++;
	}
    while (token[i])
    {
        if (token[i] == '<' || token[i] == '>' || token[i] == '|')
        {
            if (i > start)
				process_prev_str(token, start, i, cmd);
			push_back_delimited(token, &i, cmd, &start);
        }
		else
        	i++;
    }
    if (i > start)
        new_token = mk_strdup(start, i - 1, token, REMOVE);
	else
		new_token = ft_strdup("");
	return new_token;
}
