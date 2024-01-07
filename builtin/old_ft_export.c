/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_ft_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:25:44 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/07 16:40:40 by seokjyan         ###   ########.fr       */
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
		if (ft_strcmp(my_envp->key, "") != 0)
		{
			ft_putstr_fd("declare -x ", 1);
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

// int	check_key(t_envp *my_envp, char *key)
// {
// 	int	i;

// 	i = 0;
// 	while (my_envp != NULL)
// 	{
// 		if (ft_strcmp(my_envp->key, key) != 0)
// 			return (i);
// 		my_envp = my_envp->next;
// 		i++;
// 	}
// 	return (-1);
// }
// int	has_key(t_envp *my_envp, char **args, int i)
// {
// 	int		i_word;
// 	char	*key;
// 	int		i_key;
	
// 	if (ft_strrchr(args[i], (int)'=') != NULL)
// 	{
// 		i_word = 0;
// 		while (args[i][i_word] != '\0' && args[i][i_word] != '=')
// 			i_word++;
// 		key = ft_substr(args[i], 0, i_word);
// 	}
// 	else
// 		key = ft_strdup(args[i]);
// 	printf("%s\n", key);
// 	// printf("%s\n", my_envp->key);
// 	i_key = check_key(my_envp, key);
// 	if (i_key != -1)
// 	{
// 		free(key);
// 		return (i_key);
// 	}
// 	free(key);
// 	return (-1);
// }

// void	modi_envp(t_envp *my_envp, char **args,int i, int i_key)
// {
// 	int	i_c;
// 	int	i_word;

// 	i_c = 0;
// 	while (i_c < i_key)
// 		my_envp = my_envp->next;
// 	add_envp(my_envp, args, i);
// }

// void	add_export(t_envp *my_envp, char **args)
// {
// 	int	i_word;
// 	int	i_key;
// 	int	i;

// 	while (my_envp != NULL && my_envp->next != NULL)
// 		my_envp = my_envp->next;
// 	my_envp->next = (t_envp *)malloc(sizeof(t_envp));
// 	my_envp = my_envp->next;
// 	i = 1;
// 	while (args[i] != NULL)
// 	{
// 		add_envp(my_envp, args, i);
// 		i++;
// 		if (args[i] != NULL)
// 			my_envp->next = (t_envp *)malloc(sizeof(t_envp));
// 		else
// 			my_envp->next = NULL;
// 		my_envp = my_envp->next;
// 	}
// }

// int	has_key(t_envp *my_envp, char **args, int i)
// {
// 	t_envp *cp_envp;

// 	cp_envp = my_envp;
// 	while (cp_envp != NULL && cp_envp->next != NULL)
// 	{
// 		if (args[i])
// 		cp_envp = cp_envp->next;
// 	}
// 	return(-1);
// }

// int		ft_export(t_envp *my_envp, char **args, int args_cnt)
// {
// 	int	i;

// 	i = 1;
// 	if (args_cnt < 2)
// 		list_export(my_envp);
// 	else if (has_key(my_envp, args, i))
// 	{
// 		add_export(my_envp, args);
// 	}
// 	else
// 		modi_envp();
// 	return (1);
// }

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
