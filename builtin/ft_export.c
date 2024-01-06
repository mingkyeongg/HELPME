/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:25:44 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/05 20:54:14 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

// int		ft_chrpos(char *str, char c)
// {
// 	int counter;
// 	int i;

// 	counter = 0;
// 	i = 0;
// 	while (str[i] && str[i] != c)
// 	{
// 		counter++;
// 		i++;
// 	}
// 	if (str[counter] == c)
// 		return (counter);
// 	else
// 		return (-1);
// }

// void	add_env(char *name, char *value, char *envp)
// {
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	while (envp[i] != NULL)
// 		i++;
// 	i++;
// 	temp = ft_strjoin(name, "=");
// 	temp = ft_strjoin(temp, value);
// 	envp[i] = temp;
// 	envp[i + 1] = NULL;
// }

void	list_export(t_envp *my_envp)
{
	while (my_envp != NULL)
	{
		if (my_envp->key != "")
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(my_envp->key, 1);
			if (my_envp->state == HAS_EQUAL)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd(my_envp->value, 1);
				ft_putstr_fd("\n", 1);
			}
		}
		my_envp = my_envp->next;
	}
}

void	add_export(t_envp *my_envp, char **args)
{
	int	i_word;

	while (my_envp != NULL || my_envp->next != NULL)
		my_envp = my_envp->next;
	if (ft_strrchr(args[1] != NULL, (int)'=') == NULL)
	{
		my_envp->key = ft_strdup(args[1]);
		my_envp->value = "";
		my_envp->state = NO_EQUAL;
	}
	else
	{
		i_word = 0;
		while (args[1][i_word] != NULL && args[1][i_word] != '=')
			i_word++;
		my_envp->key = ft_substr(args[1], 0, i_word);
		my_envp->value = ft_strdup(args[1] + i_word + 1);
		my_envp->state = HAS_EQUAL;
	}
}

int		ft_export(t_envp *my_envp, char **args, int args_cnt)
{
	int	i;

	i = 1;
	if (args_cnt < 2)
		list_export(my_envp);
	else
		add_export(my_envp, args);
}

// int		ft_export(char **args, char **envp)
// {
// 	int		i;
// 	char	*name;
// 	char	*value;

// 	i = 0;
// 	if (!args[1] || !ft_strrchr(args[1], (int)'='))
// 		return (1);
// 	while (args[1][i] && args[1][i] != '=')
// 		i++;
// 	name = ft_substr(args[1], 0, i);
// 	i++;
// 	value = ft_strdup(args[1] + i);
// 	add_env(name, value, envp);
// 	free(name);
// 	free(value);
// 	return (0);
// }
