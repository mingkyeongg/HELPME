/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:43:26 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/13 16:52:25 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	connecting_string(char **token, char *var_value, \
	char *var_name, char *dollar_pos)
{
	char	*new_token;
	char	*temp;
	char	*next_str;

	temp = ft_strjoin(*token, var_value);
	if (return_last_dollar_pos(dollar_pos + 1) != -1)
		next_str = mk_strdup(ft_strlen(var_name) + 1, \
			return_last_dollar_pos(dollar_pos + 1), dollar_pos, LEAVE);
	else
		next_str = ft_strdup("");
	new_token = ft_strjoin(temp, next_str);
	free(*token);
	*token = NULL;
	*token = new_token;
	free(temp);
}

void	processing_after_dless(char **token)
{
	int	index;
	int	start;

	index = return_last_dollar_pos(*token);
	start = index;
	if ((*token)[index + 1] == '\0')
	{
		free(*token);
		*token = ft_strdup("");
	}
}

void	put_in_env(char **token, char **dollar_pos, t_envp *envp, t_comm **cmd)
{
	char	*var_name;
	char	*var_value;
	char	*new_dollar_pos;

	new_dollar_pos = NULL;
	var_value = NULL;
	var_name = search_env_name(*dollar_pos + 1);
	if (var_name[0] == '?')
	{
		connecting_string(token, "$?", var_name, *dollar_pos);
		return ;
	}
	var_value = ft_get_env(envp, var_name);
	if (!check_dless(*cmd))
	{
		connecting_string(token, var_name, var_name, *dollar_pos);
		return ;
	}
	if (var_value)
		connecting_string(token, var_value, var_name, *dollar_pos);
	else
		remove_undefined_env(token);
}

void	make_prev_str(char **token)
{
	int		i;
	char	*temp;

	i = return_last_dollar_pos(*token);
	temp = mk_strdup(0, i - 1, *token, LEAVE);
	free(*token);
	*token = temp;
}

int	process_env_var(char **token, t_comm **cmd, char *line, t_envp *envp)
{
	char	*dollar_pos;
	int		start;

	if (!ft_strchr(*token, '$'))
		return (0);
	dollar_pos = ft_strdup(*token);
	make_prev_str(token);
	while (ft_strchr(dollar_pos, '$'))
	{
		find_last_pos(&dollar_pos);
		put_in_env(token, &dollar_pos, envp, cmd);
		dollar_pos++;
	}
	return (0);
}
