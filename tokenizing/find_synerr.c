/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_synerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:46:49 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 14:51:08 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	pipe_at_the_end(char *buf)
{
	int	i;

	i = ft_strlen(buf) - 1;
	while (i >= 0 && buf[i] == 'S')
		i--;
	if (i > 0 && buf[i] == 'p')
	{
		if ((i >= 1 && buf[i] == 'p' && buf[i - 1] != 'p'))
			printf("minishell: syntax error near unexpected token `|'\n");
		else if (buf[i - 1] == 'p')
			printf("minishell: syntax error near unexpected token `||'\n");
		return (0);
	}
	else if (i == 0 && buf[i] == 'p')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	only_redirec(char *buf)
{
	int	i;
	int	redirection_found;

	i = 0;
	redirection_found = 0;
	while (buf[i])
	{
		if (buf[i] == 'r')
			redirection_found = 1;
		else if (buf[i] != 'S' && buf[i] != 'r')
			return (0);
		i++;
	}
	if (redirection_found)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	find_syntax_err(char *buf)
{
	if (pipe_at_the_end(buf) && !only_redirec(buf))
		return (1);
	return (0);
}
