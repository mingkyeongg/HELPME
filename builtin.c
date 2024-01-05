/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:49:29 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/29 19:21:44 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	ft_echo(t_comm *com)
{
	char	*str;

	str = NULL;
	if (!com->next->token)
		return (0);
	com = com->next;
	if (com->token != '-n')
		ft_putstr_fd(com->token, 1);
	else
	{
		com = com->next;
		ft_putstr_fd(com->token, 1);
		ft_putstr_fd('\n', 1);
	}
	return (1);
}

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

int	is_blt(t_comm *com)
{
	if(ft_strncmp(com->token, "cd", 2) == 0)
		return (1);
	if(ft_strncmp(com->token, "echo", 4) == 0)
		return (1);
	if(ft_strncmp(com->token, "env", 3) == 0)
		return (1);
	if(ft_strncmp(com->token, "exit", 4) == 0)
		return (1);
	if(ft_strncmp(com->token, "export", 6) == 0)
		return (1);
	if(ft_strncmp(com->token, "pwd", 3) == 0)
		return (1);
	if(ft_strncmp(com->token, "unset", 5) == 0)
		return (1);
	return (0);
}