/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:43:26 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/04 20:49:05 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int check_dless(t_comm *cmd)
{
	if (!cmd)
		return 1;
	while(cmd->next)
		cmd = cmd->next;
	if (cmd->type == DLESS)
		return 0;
	return 1;
}

char *search_env_name(char *str)
{
	int i = 0;
	char *name;
	int start = 0;

	while (str[i] && !is_squotes(str[i]) && !is_dquotes(str[i]) &&!is_space(str[i]))
	{
		if (is_env(str[i]))
		{
			start++;
			i++;
			continue;
		}
		i++;
	}
	name = mk_strdup(start, i - 1, str, LEAVE);
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
			new_token = mk_strdup(start, i - 1, *token, REMOVE);
			start = i + 1;
			push_back(cmd, new_token, STR);
		}
		i++;
	}
	if (i == ft_strlen(*token))
	{
		new_token = mk_strdup(start, i - 1, *token, REMOVE);
		free(*token);
		*token = new_token;
	}
}

int return_last_dollar_pos(char *str)
{
    int i = 0;
    int last_dollar = -1;  // 달러 기호가 없으면 -1을 반환

    while (str[i]) {
        if (str[i] == '$')
            last_dollar = i;  // 달러 기호의 위치를 업데이트
        i++;
    }
    return last_dollar;  // 마지막 달러 기호의 위치 반환
}

void remove_dollar(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (is_env(str[i]))
			str[i] = '\0';
		i++;
	}
}

void remove_undefined_env(char **token)
{
	char *dollar_pos = find_last_dollar(*token);
	int start = 0;
	int index = return_last_dollar_pos(*token);
	char *prev = mk_strdup(start, index -1, *token, LEAVE);
	char *next = NULL;

	while ((*token)[index] && !is_squotes((*token)[index]) && !is_dquotes((*token)[index]) &&!is_space((*token)[index]))
		index++;
	next = mk_strdup(index, ft_strlen(*token), *token, LEAVE);
	free(*token);
	*token = ft_strjoin(prev, next);
	free(prev);
	free(next);
}

char* find_last_dollar(char* str)
{
    char* last_dollar = NULL;  // 마지막으로 발견된 달러의 위치를 저장할 포인터

    const char* p = str;
    while (*p != '\0')
	{
        if (*p == '$')  // 달러 심볼 발견
            last_dollar = (char*)p;  // 위치 업데이트
		p++;
    }
    return last_dollar;  // 마지막 달러 심볼의 위치 또는 NULL 반환
}


void connecting_string(char **token, char *var_value, char *var_name, char *dollar_pos)
{
	char *new_token;
	char *temp;

	temp = ft_strjoin(*token, var_value);
	new_token = ft_strjoin(temp,  dollar_pos + ft_strlen(var_name) + 1);
    free(*token); // 원래 토큰 메모리 해제
	free(var_name);
	free(temp);
	*token = new_token;
}

void remove_quotes(char **str, int start) 
{
    char *ret = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 1));
    int i = 0;
    int j = start;

    while ((*str)[j])
	{
        if (!is_dquotes((*str)[j]))
		{
            ret[i++] = (*str)[j];
			printf("char : %c\n", (*str)[j]);
		}
        j++;
    }
    ret[i] = '\0';
    free(*str);
    *str = ret;
}

void processing_after_dless(char **token)
{
    int index;
    int start;

	index = return_last_dollar_pos(*token);
	start = index;
    if ((*token)[index + 1] == '\0')
	{
		free(*token);
		*token = ft_strdup("");
    }
}

void put_in_env(char **token, char *dollar_pos)
{
	char *var_name;
	char *var_value;

	var_name = search_env_name(dollar_pos + 1);
    var_value = getenv(var_name);
    if (var_value)
	{
        remove_dollar(dollar_pos);
		connecting_string(token, var_value, var_name, dollar_pos);
    }
	else
		remove_undefined_env(token);
}

/* 환경변수 값을 대치합니다.*/
int process_env_var(char **token, t_comm **cmd, int flag, char *line)
{
	char *dollar_pos;
    int start;

    dollar_pos = find_last_dollar(*token);
	start = 0;
    if (dollar_pos == NULL) 
		return 0; // '$' 없으면 종료
	if (!check_dless(*cmd)) // 만약 직전 토큰이 DGREAT라면
	{
		processing_after_dless(token);
		return 0;
	}
	put_in_env(token, dollar_pos);
	if (flag == UNQUOTED)
	{
		split_env(token, cmd);
		return 1;
	}
	return 0;
}
