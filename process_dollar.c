/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:43:26 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/02 21:56:56 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int check_dgreat(t_comm *cmd)
{
	if (!cmd)
		return 1;
	while(cmd->next)
		cmd = cmd->next;
	if (cmd->type == DGREAT)
		return 0;
	return 1;
}

char *search_env_name(char *str)
{
	int i = 0;
	char *name;
	int start = 0;

	while (str[i] && !is_squotes(str[i]) && !is_dquotes(str[i]))
	{
		if (is_env(str[i]))
		{
			start++;
			i++;
			continue;
		}
		i++;
	}
	name = mk_strdup(start, i - 1, str, leave);
	return name;
}

void split_env(char **token, t_comm **cmd)
{
	int i;
	int start;
	char *new_token;

	i = 0;
	start = 0;
	while ((*token)[i])
	{
		if (is_space((*token)[i]))
		{
			new_token = mk_strdup(start, i - 1, *token, remove);
			start = i + 1;
			init_list(cmd, new_token, STR);
		}
		i++;
	}
	if (i == ft_strlen(*token))
	{
		new_token = mk_strdup(start, i - 1, *token, remove);
		init_list(cmd, new_token, STR);
	}
}

int return_last_dollar(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (is_env(str[i]))
		{
			while (is_env(str[i]))
				i++;
			break;
		}
	}
	return i - 1;
}



/* 환경변수 값을 대치합니다.*/
int process_env_var(char **token, t_comm **cmd, int flag)
{
    char *var_name;
	char *var_value;
	char *new_token;
    int start = 0;

    char *dollar_pos = strchr(*token, '$');
    if (dollar_pos == NULL) 
		return 0; // '$' 없으면 종료
	if (!check_dgreat(*cmd)) // 만약 직전 토큰이 DGREAT라면
		return 0;
    var_name = search_env_name(dollar_pos + 1);
    var_value = getenv(var_name); // 환경변수 값 찾기
    if (var_value)
	{
        *dollar_pos = '\0'; // '$' 앞부분 잘라내기
        new_token = (char *)malloc(strlen(*token) + strlen(var_value) + strlen(dollar_pos + strlen(var_name) + 1) + 1);
        if (new_token) 
		{
            ft_strlcpy(new_token, *token, ft_strlen(*token) + 1); // '$' 앞부분 복사
            ft_strlcat(new_token, var_value, ft_strlen(new_token) + ft_strlen(var_value) + 1); // 환경변수 값 추가
            ft_strlcat(new_token, dollar_pos + strlen(var_name) + 1, ft_strlen(dollar_pos) - ft_strlen(var_name) + 1); // 환경변수 이름 이후 부분 추가
            free(*token); // 원래 토큰 메모리 해제
			free(var_name);
            *token = new_token; // 새 토큰으로 업데이트
        }
    }
	if (flag == UNQUOTED)
	{
		split_env(token, cmd);
		return 1;
	}
}
