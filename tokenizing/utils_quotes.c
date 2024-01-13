/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:53:52 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 15:12:00 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	process_natural_str(char **temp, t_comm **cmd, char *line)
{
	find_delimited(*temp, cmd, 0, 0);
	process_env_var(temp, cmd, UNQUOTED, line);
}

void	index_update(int *i, int *start, int quote_pos)
{
	*i = quote_pos;
	*start = quote_pos + 1;
}

void	free_temp(char **temp, char **quo_str)
{
	free(*temp);
	free(*quo_str);
	temp = NULL;
	quo_str = NULL;
}
