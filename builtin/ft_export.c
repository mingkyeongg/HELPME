/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:44:46 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/10 22:00:17 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../microshell.h"

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
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(my_envp->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		my_envp = my_envp->next;
	}
}

void	modi_export(t_envp *my_envp, char **args, int i_line, int pos)
{
	t_envp *cp_envp;
	int		i;

	cp_envp = my_envp;
	i = 0;
	while (i < pos)
	{
		cp_envp = cp_envp->next;
		i++;
	}
	if (ft_strcmp(cp_envp->value, "") == 0)
		add_envp(cp_envp, args, i_line);
}

void	add_export(t_envp *my_envp, char **args, int i_line)
{
	t_envp	*cp_envp;

	cp_envp = my_envp;
	while (cp_envp != NULL && cp_envp->next != NULL)
		cp_envp = cp_envp->next;
	cp_envp->next = (t_envp *)malloc(sizeof(t_envp));
	cp_envp = cp_envp->next;
	cp_envp->next = NULL;
	add_envp(cp_envp, args, i_line);
}

int	has_key(t_envp *my_envp, char *arg)
{
	t_envp	*cp_envp;
	int		pos;

	cp_envp = my_envp;
	pos = 0;
	while (cp_envp != NULL)
	{
		if (ft_strcmp(cp_envp->key, arg) == 0)
			return (pos);
		pos++;
		cp_envp = cp_envp->next;
	}
	return (-1);
}

int	make_key_pos(t_envp *my_envp, char *args)
{
	int		pos;
	int		i_word;
	char	*key;

	if (ft_strrchr(args, (int)'=') != NULL)
	{
		i_word = 0;
		while (args[i_word] != '\0' && args[i_word] != '=')
			i_word++;
		key = ft_substr(args, 0, i_word);
	}
	else
		key = ft_strdup(args);
	pos = has_key(my_envp, key);
	free(key);
	return (pos);
}

void	ft_export(t_envp *my_envp, char **args, int args_cnt)
{
	int		i_line;
	int		pos;

	if (args_cnt < 2)
		list_export(my_envp);
	else
	{
		i_line = 1;
		while (i_line < args_cnt)
		{
			pos = make_key_pos(my_envp, args[i_line]);
			if (pos != -1)
				modi_export(my_envp, args, i_line, pos);
			else
				add_export(my_envp, args, i_line);
			i_line++;
		}
	}
}
