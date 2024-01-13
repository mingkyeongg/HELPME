/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:40:47 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/12 15:39:04 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	ft_unset(t_envp *my_envp, char **args)
{
	char	*key;
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		key = args[i];
		while (my_envp != NULL)
		{
			if (ft_strcmp(my_envp->key, key) == 0)
				my_envp->key = "";
			my_envp = my_envp->next;
		}
		i++;
	}
}
