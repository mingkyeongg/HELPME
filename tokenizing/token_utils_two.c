/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:40:07 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/07 21:01:07 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int is_pipe(char a)
{
	if (a == '|')
		return 1;
	return 0;
}

int is_env(char a)
{
	if (a == '$')
		return 1;
	return 0;
}