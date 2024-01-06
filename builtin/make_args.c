/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:05:44 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/06 14:19:36 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	**put_args(char **args, char *token, int cnt)
{
	char	**new_args;
	int		len;
	int		i;

	len = ft_strlen(token);
	new_args = (char **)malloc(sizeof(char *) * (cnt + 1));
	i = 0;
	while (args[i] != NULL)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[cnt - 1] = token;
	new_args[cnt] = NULL;
	if (!args)
		free(args);
	return (new_args);
}

char	**make_args(t_comm *cmd, int *args_cnt)
{
	char	**args;

	*args_cnt = 0;
	args = (char **)malloc(sizeof(char *));
	args[0] = NULL;
	while (cmd != NULL || cmd->next != NULL)
	{
		if (cmd->token == NULL && cmd->next != NULL) // redirection 후 NULL처리
			cmd = cmd->next;
		(*args_cnt)++;
		args = put_args(args, cmd->token, *args_cnt);
		if (cmd->next == NULL)
			break;
		cmd = cmd->next;
	}
	return (args);
}

// char	**make_args(t_comm *cmd, int *args_cnt)
// {
// 	char	**args;

// 	*args_cnt = 0;
// 	while (cmd->token != NULL)
// 	{
// 		if (is_redirection(cmd->token) == 0 && \
// 			cmd->next != NULL && cmd->next->next != NULL)
// 			cmd = cmd->next->next;
// 		(*args_cnt)++;
// 		args = put_args(args, cmd->token, *args_cnt);
// 	}
// 	cmd->token;
// 	return (args);
// }
