/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:54:46 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/07 21:10:07 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void    ft_exit(char **args)
{
    int errnom;

    errnom = ft_atoi(args[1]);
	ft_putstr_fd("exit\n", 1);
    exit(errnom);
}