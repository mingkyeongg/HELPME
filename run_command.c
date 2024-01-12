/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:41:33 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/11 21:31:56 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	check_str(char *args)
{
	if (args == NULL)
		return (0);
	if (ft_strncmp(args, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(args, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(args, "env", 3) == 0)
		return (1);
	if (ft_strncmp(args, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(args, "export", 6) == 0)
		return (1);
	if (ft_strncmp(args, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(args, "unset", 5) == 0)
		return (1);
	return (0);
}

static int	is_builtin(t_comm *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->type == STR) // 첫번째 문자열을 마주치고
		{
			if (check_str(cmd->token) == 1) // 그 문자열이 builtin 이라면
				return (1);
			break ; // 브레이크는 확정
		}
	}
	return (0);
}

static int	is_pip(t_comm *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->type == PIPE)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	check_fork(t_comm *cmd, char **args)
{
	int	has_pipe;
	int	has_builtin;
	t_comm	*pip_cmd;
	t_comm	*blt_cmd;

	pip_cmd = cmd;
	blt_cmd = cmd;
	has_pipe = 0;
	has_builtin = 0;
	if (is_pip(pip_cmd) == 1)
		has_pipe = 1;
	if (is_builtin(blt_cmd) == 1)
		has_builtin = 1;
	if (has_pipe != 1 && has_builtin == 1)
		return (0);
	return (1);
}

void	command_not_fork(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg)
{
	ofd_arg->in_fd = dup(0);
	ofd_arg->out_fd = dup(1);
	cmd = ft_redirect_handling(cmd);
	ofd_arg->args = make_args(cmd, &ofd_arg->arg_cnt);
	if (is_blt(ofd_arg->args))
		exe_cmd(cmd, my_envp, ofd_arg->args, ofd_arg->arg_cnt);
	free_list(cmd);
	dup2(ofd_arg->in_fd, 0);
	dup2(ofd_arg->out_fd, 1);
}

int	is_pipe_arg(t_comm *cmd)
{
	t_comm	*cp_cmd;
	int 	pos;

	pos = 0;
	while (cp_cmd != NULL)
	{
		if (cmd->type == PIPE)
			return (pos);
		pos++;
		cp_cmd = cp_cmd->next;
	}
	return (0);
}

void	command_use_fork(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg)
{
	t_comm	*head_cmd;
	pid_t	pid;
	int		fd[2];
	int		pos_pipe;

	head_cmd = cmd;
	pid	= fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	pipe(fd);
	while (pos_pipe = is_pipe_arg(cmd) != 0)
	{
		cmd = ft_redirect_handling_fork(cmd);
		ofd_arg->args = make_args_fork(cmd, &ofd_arg->arg_cnt);
	}
	// if (pos_pipe = is_pipe_arg(ofd_arg->args) != 0)
	// {
	// 	pipe(fd);
	// 	pid = fork;
	// 	if (pid == -1)
	// 		perror("fork");
	// 	if (pid == 0)
	// 	{
	// 		close(fd[0]);
	// 		dup2(fd[1], 1);
	// 		exe_cmd(cmd, my_envp, ofd_arg->args, ofd_arg->arg_cnt);
	// 	}
	// 	else
	// 	{
	// 		close(fd[1]);
	// 		dup2(fd[0], 0);
	// 		exe_cmd(cmd, my_envp, ofd_arg->args[pos_pipe + 1], ofd_arg->arg_cnt);
	// 	}
	// }
}

void	run_command(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg)
{
	int	need_fork;

	need_fork = check_fork(cmd, ofd_arg->args);
	if (need_fork == 0)
		command_not_fork(cmd, my_envp, ofd_arg);
	// if (need_fork == 1)
	// 	command_use_fork(cmd, my_envp, ofd_arg);
}
