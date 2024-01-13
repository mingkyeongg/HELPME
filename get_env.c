/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:46:49 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 17:12:12 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

char	*ft_get_env(t_envp *envp, char *var_name)
{
	char	*ret;
	t_envp	*temp;

	ret = NULL;
	temp = envp;
	if (var_name[0] == '\0')
		return (ft_strdup(""));
	while (temp != NULL)
	{
		if (ft_strcmp(var_name, temp->key) == 0)
		{
			ret = ft_strdup(temp->value);
			return (ret);
		}
		temp = temp->next;
	}
	return (ft_strdup(""));
}
