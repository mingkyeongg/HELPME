/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:49:29 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/10 20:58:55 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	exe_cmd(t_envp *my_envp, char **args, int args_cnt)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		ft_cd(args);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(my_envp);
	// else if (ft_strncmp(args[0], "exit", 4) == 0)
		// ft_exit(args);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ft_export(my_envp, args, args_cnt);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd(args);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_unset(my_envp, args);
	// else
	// 	ft_execve(args);
}

int	is_blt(char **args)
{
	if (args[0] == NULL)
		return (0);
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
