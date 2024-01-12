/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:46:04 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/12 15:40:07 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	add_envp(t_envp *my_envp, char **envp, int i_line)
{
	int	i_word;

	if (ft_strrchr(envp[i_line], (int)'=') == NULL)
	{
		my_envp->key = ft_strdup(envp[i_line]);
		my_envp->value = "";
		my_envp->state = NO_EQUAL;
	}
	else
	{
		i_word = 0;
		while (envp[i_line][i_word] != '\0' && envp[i_line][i_word] != '=')
			i_word++;
		my_envp->key = ft_substr(envp[i_line], 0, i_word);
		my_envp->value = ft_strdup(envp[i_line] + i_word + 1);
		my_envp->state = HAS_EQUAL;	
	}
}

t_envp	*make_envp(char **envp)
{
	t_envp	*my_envp;
	t_envp	*my_envp_head;
	int		i_line;
	int		i_word;

	my_envp = (t_envp *)malloc(sizeof(t_envp));
	my_envp_head = my_envp;
	i_line = 0;
	while (envp[i_line] != NULL)
	{
		add_envp(my_envp, envp, i_line);
		i_line++;
		if (envp[i_line] != NULL)
			my_envp->next = (t_envp *)malloc(sizeof(t_envp));
		else
			my_envp->next = NULL;
		my_envp = my_envp->next;
	}
	return (my_envp_head);
}

// t_envp	*make_envp(char **envp)
// {
// 	t_envp	*my_envp;
//     t_envp  *my_envp_head;
// 	int		i_line;
// 	int		i_word;

// 	my_envp = (t_envp *)malloc(sizeof(t_envp));
//     my_envp_head = my_envp;
// 	i_line = 0;
// 	while (envp[i_line] != NULL)
// 	{
// 		if (ft_strrchr(envp[i_line], (int)'=') == NULL)
// 		{
// 			my_envp->key = ft_strdup(envp[i_line]);
// 			my_envp->value = "";
// 			my_envp->state = NO_EQUAL;
// 		}
// 		else
// 		{
// 			i_word = 0;
// 			while (envp[i_line][i_word] != '\0' && envp[i_line][i_word] != '=')
// 				i_word++;
// 			my_envp->key = ft_substr(envp[i_line], 0, i_word);
// 			my_envp->value = ft_strdup(envp[i_line] + i_word + 1);
// 			my_envp->state = HAS_EQUAL;
			
// 		}
//         i_line++;
// 		if (envp[i_line] != NULL)
// 			my_envp->next = (t_envp *)malloc(sizeof(t_envp));
// 		else
// 			my_envp->next = NULL;
// 		my_envp = my_envp->next;
// 	}
// 	return (my_envp_head);
// }
