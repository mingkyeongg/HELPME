/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:22:38 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/13 16:25:23 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	command_use_fork(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg)
{
    pid_t   pid;
    t_comm  *old_cmd;
    int     fd[2];

    old_cmd = cmd;
    pipe(fd);
    cmd = move_cmd(cmd);
    ofd_arg->pid[ofd_arg->i_pid] = fork();
    if (ofd_arg->pid[ofd_arg->i_pid] == -1)
    {
        perror("fork");
        return ;
    }
    if (ofd_arg->pid[ofd_arg->i_pid] == 0)
    {
        close(fd[0]);
        if (cmd != NULL)
        {
		    dup2(fd[1], 1);
        }
        close(fd[1]);
        ft_redirect_handling(old_cmd);
        ofd_arg->args = make_args_fork(old_cmd, &ofd_arg->arg_cnt);
        exe_cmd(old_cmd, my_envp, ofd_arg->args, ofd_arg->arg_cnt);
        if (is_blt(ofd_arg->args))
            exit(0);
    }
	else
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        if (cmd != NULL)
        {
            ofd_arg->i_pid++;
            command_use_fork(cmd, my_envp, ofd_arg);
        }
    }
}
