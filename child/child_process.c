/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:22:38 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/12 17:19:23 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	command_use_fork(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg)
{
    pid_t   pid;
    int     fd[2];
    int     cnt_pipe;
    int     pos_pips;

    pipe(fd);
    ofd_arg->pid[ofd_arg->i_pid] = fork();
    if (ofd_arg->pid[ofd_arg->i_pid] == -1)
    {
        perror("fork");
        return ;
    }
    if (ofd_arg->pid[ofd_arg->i_pid] == 0)
    {
        ft_redirect_handling(cmd);
        ofd_arg->args = make_args_fork(cmd, &ofd_arg->arg_cnt);
		close(fd[0]);
		dup2(fd[1], 1);
        exe_cmd(cmd, my_envp, ofd_arg->args, ofd_arg->arg_cnt);
    }
	else
    {
        close(fd[1]);
        dup2(fd[0], 0);
        if (cmd != NULL)
            command_use_fork(cmd, my_envp, ofd_arg);
    }
}

