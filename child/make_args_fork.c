/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:16:13 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/12 15:38:50 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	**make_args_fork(t_comm *cmd, int *args_cnt)
{
	char	**args;

	*args_cnt = 0;
	args = (char **)malloc(sizeof(char *));
	args[0] = NULL;
	while (cmd != NULL)
	{
		if (cmd->token == NULL) // redirection is NULL
		{
			cmd = cmd->next;
			continue ;
		}
        if (cmd->type == PIPE)
        {
		    cmd = cmd->next; // return pointer -> PIPE next
            break ;
		}
        (*args_cnt)++;
		args = put_args(args, cmd->token, *args_cnt);
		if (cmd->next == NULL)
			break;
		cmd = cmd->next;
	}
	return (args);
}
