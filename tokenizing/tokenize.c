/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:33:37 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 15:12:24 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	print(t_comm *cmd)
{
	while (cmd)
	{
		printf("token : %s             \
			stype : %d      length : %d\n", cmd->token, cmd->type, cmd->length);
		cmd = cmd->next;
	}
}

char	*mk_strdup(int start, int end, char *line, int flag)
{
	char	*new_line;
	int		i;
	int		j;

	if (start > end)
		return (ft_strdup(""));
	new_line = (char *)malloc(sizeof(char) * (end - start + 2));
	if (new_line == NULL)
		exit(1);
	i = 0;
	j = start;
	while (j <= end)
	{
		if (line[j] == '\0')
			break ;
		if (!is_space(line[j]) && flag == REMOVE)
			new_line[i++] = line[j];
		else if (flag == LEAVE)
			new_line[i++] = line[j];
		j++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	creat_string(char *line, t_comm **cmd, int start, int end)
{
	char	*temp;

	temp = find_delimited(mk_strdup(start, end, line, REMOVE), cmd, 0, 0);
	process_env_var(&temp, cmd, UNQUOTED, line);
	push_back(cmd, temp, STR);
	free(temp);
}

void	split_line(char *line, t_comm **cmd)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i + 1] == '\0' || is_space(line[i]))
		{
			creat_string(line, cmd, start, i);
			start = i + 1;
		}
		else if (is_squotes(line[i]) || is_dquotes(line[i]))
			process_in_quotes(line, &i, &start, cmd);
		else if (line[i] == '#')
		{
			creat_string(line, cmd, start, i - 1);
			break ;
		}
		i++;
	}
	print(*cmd);
}
