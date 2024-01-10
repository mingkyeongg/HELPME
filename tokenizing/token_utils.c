/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:39:26 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/07 21:01:04 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int is_del(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
			return 1;
	}
	return 0;
}

int is_space(char a)
{
	if (a == 32 || (a >= 9 && a <= 13))
		return 1;
	return 0;
}

int is_dquotes(char a)
{
	if (a == '"')
		return 1;
	return 0;
}

int is_squotes(char a)
{
	if (a == '\'')
		return 1;
	return 0;
}

int is_redirect(char a)
{
	if (a == '<' || a == '>')
		return 1;
	return 0;
}