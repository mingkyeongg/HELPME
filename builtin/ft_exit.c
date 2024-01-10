/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:54:46 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/10 22:04:44 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void    ft_exit(t_comm *cmd, char **args)
{
    int errnom;

    if (args[1] != NULL)
        errnom = ft_atoi(args[1]);
	else
        errnom = 1;
    ft_putstr_fd("exit\n", 1);
	free_list(cmd);
    exit(errnom);
}