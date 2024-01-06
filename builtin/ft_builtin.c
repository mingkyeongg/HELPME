/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:49:29 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/05 18:00:06 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	exe_cmd(char **args, int args_cnt)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		ft_cd(args);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(args);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		ft_exit(args);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ft_export(args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd(args);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_unset(args);
	else
		ft_execve(args);
}

int	is_blt(char **args)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		return (1);
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (1);
	if (ft_strncmp(args[0], "env", 3) == 0)
		return (1);
	if (ft_strncmp(args[0], "exit", 4) == 0)
		return (1);
	if (ft_strncmp(args[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(args[0], "unset", 5) == 0)
		return (1);
	return (0);
}
