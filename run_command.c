/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:41:33 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/13 18:03:07 by seokjyan         ###   ########.fr       */
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
	t_comm	*cp_cmd;

	cp_cmd = cmd;
	while (cp_cmd != NULL)
	{
		if (cp_cmd->type == STR) // here first STR
		{
			if (check_str(cp_cmd->token) == 1) // STR is builtin
				return (1);
			break ; // most break ;
		}
	}
	return (0);
}

static int	is_pip(t_comm *cmd)
{
	t_comm *cp_cmd;
	int		cmd_cnt;

	cp_cmd = cmd;
	cmd_cnt = 1;
	while (cp_cmd != NULL)
	{
		if (cp_cmd->type == PIPE)
			cmd_cnt++;
		cp_cmd = cp_cmd->next;
	}
	return (cmd_cnt);
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

void	run_command(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg)
{
	int	need_fork;
	int	builtin;
	int	cmd_count;
	int	status;
	int	i;

	ft_heredoc(cmd);
	builtin = is_builtin(cmd); // first cmd builtin ret 1
	cmd_count = is_pip(cmd); // return cmd, default 1 meet pipe ++
	if (builtin == 1 && cmd_count == 1)
		command_not_fork(cmd, my_envp, ofd_arg);
	else
	{
		ofd_arg->in_fd = dup(0);
		ofd_arg->out_fd = dup(1);
		ofd_arg->pid = (int *)malloc(sizeof(int) * cmd_count);
		ofd_arg->i_pid = 0;
		command_use_fork(cmd, my_envp, ofd_arg);
		dup2(ofd_arg->in_fd, 0);
		dup2(ofd_arg->out_fd, 1);
		i = 0;
		while (i < cmd_count)
		{
			waitpid(ofd_arg->pid[i], &status, 0);
			i++;
		}
	}
}

// int	is_pipe_arg(t_comm *cmd)
// {
// 	t_comm	*cp_cmd;
// 	int 	pos;

// 	pos = 0;
// 	while (cp_cmd != NULL)
// 	{
// 		if (cmd->type == PIPE)
// 			return (pos);
// 		pos++;
// 		cp_cmd = cp_cmd->next;
// 	}
// 	return (0);
// }

// void	command_use_fork(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg)
// {
// 	t_comm	*head_cmd;
// 	pid_t	pid;
// 	int		fd[2];
// 	int		pos_pipe;

// 	head_cmd = cmd;
// 	pid	= fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return ;
// 	}
// 	pipe(fd);
// 	while (pos_pipe = is_pipe_arg(cmd) != 0)
// 	{
// 		cmd = ft_redirect_handling_fork(cmd);
// 		ofd_arg->args = make_args_fork(cmd, &ofd_arg->arg_cnt);
// 	}
// 	// if (pos_pipe = is_pipe_arg(ofd_arg->args) != 0)
// 	// {
// 	// 	pipe(fd);
// 	// 	pid = fork;
// 	// 	if (pid == -1)
// 	// 		perror("fork");
// 	// 	if (pid == 0)
// 	// 	{
// 	// 		close(fd[0]);
// 	// 		dup2(fd[1], 1);
// 	// 		exe_cmd(cmd, my_envp, ofd_arg->args, ofd_arg->arg_cnt);
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		close(fd[1]);
// 	// 		dup2(fd[0], 0);
// 	// 		exe_cmd(cmd, my_envp, ofd_arg->args[pos_pipe + 1], ofd_arg->arg_cnt);
// 	// 	}
// 	// }
// }
