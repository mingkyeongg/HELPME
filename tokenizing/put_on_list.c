/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_on_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:36:23 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 15:08:39 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	prev_check(t_comm **cmd, char *token, int type)
{
	char	*new_token;
	t_comm	*temp;

	if (*cmd == NULL)
		return (1);
	temp = *cmd;
	while (temp -> next)
		temp = temp->next;
	if (temp->type == CONTINUE)
	{
		new_token = ft_strjoin(temp->token, token);
		free(temp->token);
		temp->token = new_token;
		temp->type = type;
		temp->length += ft_strlen(token);
		return (0);
	}
	return (1);
}

t_comm	*make_node(char *token, int type)
{
	t_comm	*push;

	push = (t_comm *)malloc(sizeof(t_comm));
	push->token = ft_strdup(token);
	push->length = ft_strlen(token);
	push->next = NULL;
	if (type == QUOTED)
		push->type = STR;
	else
		push->type = type;
	return (push);
}

void	push_back(t_comm **cmd, char *token, int type)
{
	t_comm	*push;
	t_comm	*temp;

	if (token[0] == '\0' && type != QUOTED)
		return ;
	if (!token)
		return ;
	if (!prev_check(cmd, token, type))
		return ;
	push = make_node(token, type);
	if (*cmd == NULL)
		*cmd = push;
	else
	{
		temp = *cmd;
		while (temp->next)
			temp = temp->next;
		temp->next = push;
	}
}
