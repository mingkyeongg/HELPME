/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_on_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:36:23 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/11 13:03:05 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int prev_check(t_comm **cmd, char *token, int type)
{
	char *new_token;

	if (*cmd == NULL)
		return 1;
	t_comm *temp = *cmd;
	while (temp -> next)
		temp = temp->next;
	if (temp->type == CONTINUE)
	{
		new_token = ft_strjoin(temp->token, token);
		free(temp->token);
		temp->token = new_token;
		temp->type = type;
		temp->length += ft_strlen(token);
		return 0;
	}
	return 1;
}

void push_back(t_comm **cmd, char *token, int type)
{
	if (token[0] == '\0' && type != QUOTED)
		return;
	if(!token)
		return;
	if (!prev_check(cmd, token, type))
		return;
    t_comm *push = (t_comm *)malloc(sizeof(t_comm));
    if (!push) 
		exit(1);
    push->token = ft_strdup(token);
    push->length = ft_strlen(token);
	if (type == QUOTED)
		push->type = STR;
	else
    	push->type = type;
    push->next = NULL;
    if (*cmd == NULL)
        *cmd = push;
    else
	{
        t_comm *temp = *cmd;
        while (temp->next)
            temp = temp->next;
        temp->next = push;
    }
}
