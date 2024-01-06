/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_envp_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:44:45 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/06 15:46:27 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	print_my_envp(t_envp *my_envp)
{
	while (my_envp != NULL)
	{
		if (ft_strcmp(my_envp->key, "") == 0)
			printf("key =	\"\"\n");
		else
			printf("key =	%s\n", my_envp->key);
		if (ft_strcmp(my_envp->value, "") == 0)
			printf("value =	\"\"\n");
		else
			printf("value =	%s\n\n", my_envp->value);
		my_envp = my_envp->next;
	}
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		printf("args[%d] %s\n", i, args[i]);
		i++;
	}
}
