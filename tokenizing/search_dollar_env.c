/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_dollar_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:46:03 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 15:07:36 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	check_dless(t_comm *cmd)
{
	if (!cmd)
		return (1);
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->type == DLESS)
		return (0);
	return (1);
}

char	*search_env_name(char *str)
{
	int		i;
	char	*name;
	int		start;
	int		flag;

	i = 0;
	start = 0;
	flag = 0;
	while (str[i] && !is_squotes(str[i]) && !is_dquotes(str[i]) \
		&&!is_space(str[i]) && !is_env(str[i]))
	{
		if (is_env(str[i]))
		{
			start++;
			i++;
			continue ;
		}
		i++;
	}
	name = mk_strdup(start, i - 1, str, LEAVE);
	return (name);
}

int	return_last_dollar_pos(char *str)
{
	int	i;
	int	last_dollar;
	int	flag;

	i = 0;
	last_dollar = -1;
	flag = 0;
	while (str[i] && flag == 0)
	{
		while (str[i] == '$')
		{
			last_dollar = i;
			flag = 1;
			i++;
		}
		i++;
	}
	return (last_dollar);
}

char	*find_last_dollar(char *str)
{
	char		*last_dollar;
	const char	*p;
	int			flag;

	last_dollar = NULL;
	p = str;
	flag = 0;
	while (*p != '\0' && flag == 0)
	{
		while (*p == '$')
		{
			last_dollar = (char *)p;
			p++;
			flag = 1;
		}
		p++;
	}
	return (last_dollar);
}

void	find_last_pos(char **str)
{
	char	*p;
	char	*last_dollar;
	int		flag;

	p = *str;
	last_dollar = NULL;
	flag = 0;
	while (*p != '\0' && flag == 0)
	{
		while (*p == '$')
		{
			last_dollar = (char *)p;
			p++;
			flag = 1;
		}
		p++;
	}
	*str = last_dollar;
}
