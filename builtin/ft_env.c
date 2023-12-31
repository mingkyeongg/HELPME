/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:59:22 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/07 20:29:28 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void    ft_env(t_envp *my_envp)
{
	while (my_envp != NULL)
	{
		if (ft_strcmp(my_envp->key, "") != 0)
		{
			ft_putstr_fd(my_envp->key, 1);
			if (my_envp->state == HAS_EQUAL)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd(my_envp->value, 1);
			}
			ft_putstr_fd("\n", 1);
		}
		my_envp = my_envp->next;
	}
}