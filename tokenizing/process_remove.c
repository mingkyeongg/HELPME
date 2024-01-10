/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:48:23 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/07 21:01:06 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void split_env(char **token, t_comm **cmd)
{
	int i;
	int start;
	char *new_token;

	i = 0;
	start = 0;
	while ((*token)[i])
	{
		if (is_space((*token)[i]))
		{
			new_token = mk_strdup(start, i - 1, *token, REMOVE);
			start = i + 1;
			push_back(cmd, new_token, STR);
		}
		i++;
	}
	if (i == ft_strlen(*token))
	{
		new_token = mk_strdup(start, i - 1, *token, REMOVE);
		free(*token);
		*token = new_token;
	}
}

void remove_dollar(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (is_env(str[i]))
			str[i] = '\0';
		i++;
	}
}

void remove_undefined_env(char **token)
{
	char *dollar_pos = find_last_dollar(*token);
	int start = 0;
	int index = return_last_dollar_pos(*token);
	char *prev = mk_strdup(start, index -1, *token, LEAVE);
	char *next = NULL;

	while ((*token)[index] && !is_squotes((*token)[index]) && !is_dquotes((*token)[index]) &&!is_space((*token)[index]))
		index++;
	next = mk_strdup(index, ft_strlen(*token), *token, LEAVE);
	free(*token);
	*token = ft_strjoin(prev, next);
	free(prev);
	free(next);
}

void remove_quotes(char **str, int start) 
{
    char *ret = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 1));
    int i = 0;
    int j = start;

    while ((*str)[j])
	{
        if (!is_dquotes((*str)[j]))
		{
            ret[i++] = (*str)[j];
			printf("char : %c\n", (*str)[j]);
		}
        j++;
    }
    ret[i] = '\0';
    free(*str);
    *str = ret;
}