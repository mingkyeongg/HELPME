/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:49:57 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/12 22:13:18 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	ft_heredoc(t_comm *cmd)
{
	int	*old_fd_0;
	int	*old_fd_1;


	*old_fd_0 = -1;
	*old_fd_1 = -1;
	while (cmd != NULL)
	{
		if (cmd->type == DLESS && cmd->next != NULL)
		{
			pipe(cmd->fd);
			if (old_fd_0 != -1)
			{
				old_fd_0 = cmd->fd[0];
				old_fd_1 = cmd->fd[1];
				
			}
			else
			{
				close(*old_fd_0);
				close(*old_fd_1);
			}
		}
		cmd = cmd->next;
	}	
}