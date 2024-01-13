/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:27:34 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/11 21:06:39 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int is_redirection(char *token)
{
	if (ft_strcmp(token, ">") == 0)
		return (GREAT);
	else if (ft_strcmp(token, ">>") == 0)
		return (DGREAT);
	else if (ft_strcmp(token, "<") == 0)
		return (LESS);
	else if (ft_strcmp(token, "<<") == 0)
		return (DLESS);
	return (0);
}

t_comm 	*ft_redirect_handling_fork(t_comm *cmd)
{
	int		get_type;

	while (cmd != NULL && cmd->type != PIPE)
	{
		get_type = is_redirection(cmd->token);
		if (get_type != 0)
		{
			if (cmd->next != NULL)
			{
				exe_redirection(cmd->next->token, get_type);
				cmd->token = NULL;
				cmd->next->token = NULL;
				cmd = cmd->next->next;
			}
			else
				cmd = cmd->next;
		}
		else
			cmd = cmd->next;
	}
	return (cmd);
}

t_comm 	*ft_redirect_handling(t_comm *cmd)
{
	t_comm *head_cmd;
	int		get_type;

	head_cmd = cmd;
	while (cmd != NULL && cmd->type != PIPE)
	{
		get_type = is_redirection(cmd->token);
		if (get_type != 0)
		{
			if (cmd->next != NULL)
			{
				exe_redirection(cmd->next->token, get_type);
				cmd->token = NULL;
				cmd->next->token = NULL;
				cmd = cmd->next->next;
			}
			else
				cmd = cmd->next;
		}
		else
			cmd = cmd->next;
	}
	return (head_cmd);
}
