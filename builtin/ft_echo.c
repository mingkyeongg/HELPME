/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:36:07 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/07 20:28:45 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void    ft_echo(char **args)// -nnnn수정해야함
{
	int	i_line;
	int	i_word;
	
	i_line = 1;
	while (args[i_line] != NULL && ft_strncmp(args[i_line], "-", 1) == 0)
	{
		i_word = 1;
		while (args[i_line][i_word] != '\0' && args[i_line][i_word] == 'n')
			i_word++;
		if (args[i_line][i_word] == '\0')
			i_line++;
		else
			break ;
	}
	while (args[i_line] != NULL)
	{
		ft_putstr_fd(args[i_line], 1);
		i_line++;
		if (args[i_line] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (args[1] != NULL && ft_strncmp(args[1], "-n", 2) != 0)
		ft_putstr_fd("\n", 1);
}
