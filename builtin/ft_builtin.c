/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:49:29 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/04 17:29:31 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	exe_cmd(t_comm *cur)
{
	if (ft_strncmp(cur->token, "cd", 2) == 0)
		ft_cd(cur);
	else if (ft_strncmp(cur->token, "echo", 4) == 0)
		ft_echo(cur);
	else if (ft_strncmp(cur->token, "env", 3) == 0)
		ft_env(cur);
	else if (ft_strncmp(cur->token, "exit", 4) == 0)
		ft_exit(cur);
	else if (ft_strncmp(cur->token, "export", 6) == 0)
		ft_export(cur);
	else if (ft_strncmp(cur->token, "pwd", 3) == 0)
		ft_pwd(cur);
	else if (ft_strncmp(cur->token, "unset", 5) == 0)
		ft_unset(cur);
	else
		ft_execve(cur);
}

int	is_blt(t_comm *cur)
{
	if (ft_strncmp(cur->token, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cur->token, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cur->token, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cur->token, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cur->token, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cur->token, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cur->token, "unset", 5) == 0)
		return (1);
	else
		return (1);
}

char	**put_args(char **args, char *token, int cnt)
{
	char	**new_args;
	int		len;
	int		i;

	len = ft_strlen(token);
	new_args = (char **)malloc(sizeof(char *) * (cnt + 1));
	i = 0;
	while (args[i] != NULL)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[cnt - 1] = token;
	new_args[cnt] = '\0';
	if (!args)
		free(args);
	return (new_args);
}

char	**make_args(t_comm *com)
{
	int		cnt;
	char	**args;

	cnt = 0;
	while (com->token != NULL)
	{
		if (is_redirection(com->token) == 0 && \
			com->next != NULL && com->next->next != NULL)
			com = com->next->next;
		cnt++;
		args = put_args(args, com->token, cnt);
	}
	com->token;
	return (args);
}
