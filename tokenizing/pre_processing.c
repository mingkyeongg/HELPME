/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:33:05 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 16:07:48 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	fill_buf(char *line, char *buf)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			buf[i] = 'S';
		else if (is_dquotes(line[i]))
			buf[i] = 'Q';
		else if (is_squotes(line[i]))
			buf[i] = 'q';
		else if (is_pipe(line[i]))
			buf[i] = 'p';
		else if (is_redirect(line[i]))
			buf[i] = 'r';
		else if (line[i] == '$')
			buf[i] = 'D';
		else
			buf[i] = 'A';
		i++;
	}
}

int	tokenizing(char *line, t_comm **cmd, int i, t_envp *envp)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * strlen(line) + 1);
	bzero(buf, strlen(line) + 1);
	fill_buf(line, buf);
	if (!find_syntax_err(buf))
	{
		free(buf);
		return (0);
	}
	split_line(line, cmd, envp);
	return (1);
}

int	read_input(t_comm **cmd, t_envp *envp)
{
	char	*read;

	read = readline("minishell$ ");
	if (read == NULL)
		exit(0);
	if (!tokenizing(read, cmd, 0, envp))
	{
		add_history(read);
		free(read);
		return (0);
	}
	add_history(read);
	free(read);
	return (1);
}

void	free_list(t_comm *cmd)
{
	t_comm	*temp;

	while (cmd != NULL)
	{
		temp = cmd;
		cmd = cmd->next;
		free(temp->token);
		free(temp);
	}
}
