/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_inside_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:03:56 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 15:18:43 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	*process_squo(char *line, int *i, int *start, t_comm **cmd)
{
	int		quote_pos;
	char	*squo_str;
	char	*temp;
	char	*token;

	quote_pos = *i + 1;
	if (*i > *start)
	{
		temp = mk_strdup(*start, *i - 1, line, REMOVE);
		process_natural_str(&temp, cmd, line);
	}
	else
		temp = ft_strdup("");
	while (line[quote_pos] && !is_squotes(line[quote_pos]))
		quote_pos++;
	if (is_squotes(line[quote_pos]))
	{
		squo_str = mk_strdup(*i + 1, quote_pos - 1, line, LEAVE);
		token = ft_strjoin(temp, squo_str);
		index_update(i, start, quote_pos);
		free_temp(&temp, &squo_str);
		return (token);
	}
	free(temp);
	return (NULL);
}

char	*process_dquo(char *line, int *i, int *start, t_comm **cmd)
{
	int		quote_pos;
	char	*dquo_str;
	char	*temp;
	char	*token;

	quote_pos = *i + 1;
	temp = mk_strdup(*start, *i - 1, line, REMOVE);
	process_natural_str(&temp, cmd, line);
	while (line[quote_pos] && !is_dquotes(line[quote_pos]))
		quote_pos++;
	if (is_dquotes(line[quote_pos]))
	{
		dquo_str = mk_strdup(*i + 1, quote_pos - 1, line, LEAVE);
		process_env_var(&dquo_str, cmd, QUOTED, line);
		token = ft_strjoin(temp, dquo_str);
		index_update(i, start, quote_pos);
		free_temp(&temp, &dquo_str);
		return (token);
	}
	free(temp);
	return (NULL);
}

void	push_quote_string(t_comm **cmd, char *line, int index, char **temp)
{
	if ((!line[index + 1] || is_space(line[index + 1])) && *temp)
		push_back(cmd, *temp, QUOTED);
	else
		push_back(cmd, *temp, CONTINUE);
	free(*temp);
}

void	process_in_quotes(char *line, int *index, int *start, t_comm **cmd)
{
	char	*temp;

	temp = NULL;
	if (is_squotes(line[*index]))
		temp = process_squo(line, index, start, cmd);
	else
		temp = process_dquo(line, index, start, cmd);
	push_quote_string(cmd, line, *index, &temp);
}
