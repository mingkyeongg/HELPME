/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:36:07 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/06 16:09:13 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void    ft_echo(char **args)// -nnnn수정해야함
{
	int	i;
	
	i = 1;
	if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
		i++;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (args[i] == NULL && ft_strcmp(args[1], "-n") != 0)
		ft_putstr_fd("\n", 1);
}
