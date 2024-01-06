/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:05:44 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/05 19:24:16 by seokjyan         ###   ########.fr       */
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
	new_args[cnt] = '\0';
	if (!args)
		free(args);
	return (new_args);
}

char	**make_args(t_comm *com, int *args_cnt)
{
	char	**args;

	*args_cnt = 0;
	while (com->token != NULL)
	{
		if (is_redirection(com->token) == 0 && \
			com->next != NULL && com->next->next != NULL)
			com = com->next->next;
		(*args_cnt)++;
		args = put_args(args, com->token, *args_cnt);
	}
	com->token;
	return (args);
}