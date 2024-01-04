/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:25:44 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/04 18:52:47 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int		ft_chrpos(char *str, char c)
{
	int counter;
	int i;

	counter = 0;
	i = 0;
	while (str[i] && str[i] != c)
	{
		counter++;
		i++;
	}
	if (str[counter] == c)
		return (counter);
	else
		return (-1);
}

void	add_env(char *name, char *value, char *envp)
{
	char	*temp;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	i++;
	temp = ft_strjoin(name, "=");
	temp = ft_strjoin(temp, value);
	envp[i] = temp;
	envp[i + 1] = NULL;
}

int		ft_export(char **args, char **envp)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	if (!args[1] || !ft_strrchr(args[1], (int)'='))
		return (1);
	while (args[1][i] && args[1][i] != '=')
		i++;
	name = ft_substr(args[1], 0, i);
	i++;
	value = ft_strdup(args[1] + i);
	add_env(name, value, envp);
	free(name);
	free(value);
	return (0);
}
