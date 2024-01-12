/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:44:48 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/12 19:58:02 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

t_comm  *move_cmd(t_comm *cmd)
{
    t_comm	*mv_cmd;
	
	mv_cmd = cmd;
	while (1)
	{
		if (mv_cmd == NULL || mv_cmd->type == PIPE)
			break ;
		printf("mv token = %s\n",mv_cmd->token);
		mv_cmd = mv_cmd->next;
    }
	if (mv_cmd != NULL)
		mv_cmd = mv_cmd->next;
	printf("exit\n");
	return (mv_cmd);
}