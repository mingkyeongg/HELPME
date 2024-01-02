/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:33:37 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/02 22:30:13 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

/*


	문제
	1. 환경변수로 개긴 문자열 오면 터져버림 ㅠㅠ
	2. 놈 맞추기
*/

void print(t_comm *cmd)
{
	while (cmd)
	{
		printf("token : %s             type : %d\n", cmd->token, cmd->type);
		cmd = cmd->next;
	}
}

/* start ~ end 까지의 문자열 반환하는 함수 */
char *mk_strdup(int start, int end, char *line, int flag)
{
    char *new_line;
    int i, j;

    // 메모리 할당 (길이 계산은 동일하게 유지)
    new_line = (char *)malloc(sizeof(char) * (end - start + 2));
    if (new_line == NULL)
        return NULL;  // 할당 실패 시 NULL 반환

    i = 0;  // 새 문자열의 인덱스
    j = start;  // 원본 문자열의 인덱스
    while (j <= end)
	{
        if (line[j] == '\0') 
            break;  // 원본 문자열의 끝에 도달
        if (!is_space(line[j]) && flag == remove)
            new_line[i++] = line[j];
		else
			new_line[i++] = line[j];
        j++;
    }
    new_line[i] = '\0';  // 새 문자열 끝에 널 종료 문자 추가
    return new_line;
}


char *find_delimited(char *token, t_comm **cmd)
{
    int i = 0;
    int start = 0;
    char *new_token;
	int del_flag = 0;

    while (token[i])
    {
        // 리다이렉션과 파이프 기호 처리
		while(is_space(token[i]))
			start++;
        if (token[i] == '<' || token[i] == '>' || token[i] == '|')
        {
            // 현재까지의 일반 문자열 출력
            if (i > start)
            {
                new_token = mk_strdup(start, i - 1, token, remove);
				process_env_var(&new_token, cmd, UNQUOTED);
                init_list(cmd, new_token, STR);
                free(new_token);
            }
			// 파이프 출력
			if (token[i] == '|')
			{
				new_token = mk_strdup(i, i, token, remove);
				init_list(cmd, new_token, PIPE);
				i++;
			}

            // 리다이렉션과 기호 출력
            else if ((token[i] == '<' || token[i] == '>') && token[i + 1] == token[i])
            {
                new_token = mk_strdup(i, i + 1, token, remove);
				if (new_token[0] == '<')
					init_list(cmd, new_token, DLESS);
				else
					init_list(cmd, new_token, DGREAT);
                i += 2;
            }
            else
            {
                new_token = mk_strdup(i, i, token, remove);
				if (new_token[0] == '<')
					init_list(cmd, new_token, LESS);
				else
					init_list(cmd, new_token, GREAT);
                i++;
            }
            free(new_token);
            start = i;
        }
        else
            i++;
    }
    // 마지막 일반 문자열이 있으면 리턴
    if (i > start)
        new_token = mk_strdup(start, i - 1, token, remove);
	else // 없으면 빈문자열 리턴
		new_token = ft_strdup("");
	return new_token;
}

int process_dquo(char *line, int start, char **temp, t_comm **cmd)
{
    int end = start + 1;
    char *token;
	char *isolation;
	char *ret;

	isolation = find_delimited(*temp, cmd);
    while (line[end])
    {
        if (is_dquotes(line[end]))
		{
            token = mk_strdup(start + 1, end - 1, line, leave);
			break;
		}
        end++;
    }

	memset(*temp, 0, strlen(line));
	strcat(*temp, isolation);
	process_env_var(&token, cmd, QUOTED);
	ret = ft_strjoin(*temp, token);
	free(*temp);
	free(token);
	*temp = ret;
    return end;
}

int process_squo(char *line, int start, char **temp, t_comm **cmd)
{
    int end = start + 1;
    char *token;
	char *ret;

    while (line[end])
    {
        if (is_squotes(line[end]))
		{
            token = mk_strdup(start + 1, end - 1, line, leave);
			break;
		}
        end++;
    }
	memset(*temp, 0, strlen(line));
	// ret = ft_strjoin(*temp, token);
	// free(temp);
	// *temp = ret;
	// free(ret);
	strcat(*temp, token);
    return end;
}

void init_list(t_comm **cmd, char *token, int type)
{
	if (token[0] == '\0')
		return;
    t_comm *push = (t_comm *)malloc(sizeof(t_comm));
    if (!push) return;  // 메모리 할당 확인
 
    push->token = strdup(token);
    push->length = ft_strlen(token);
    push->type = type;
    push->next = NULL;

    // 리스트의 끝을 찾고 새 노드 추가
    if (*cmd == NULL) {
        *cmd = push;
    } else {
        t_comm *temp = *cmd;
        while (temp->next)
            temp = temp->next;
        temp->next = push;
    }
}

void process_temp(char **temp, char *str)
{
	int new_len = ft_strlen(*temp) + ft_strlen(str) + 1;
	char *ret;

	if (*(temp)[0] == '\0')
		ret = ft_strdup(str);
	else
		ret = ft_strjoin(*temp, str);
	free(*temp);
	*temp = ret;
	free(ret);
}

/* 문자를 나눠용 */
void split_line(char *line, t_comm **cmd)
{
	int i = 0;
	int token_index = 0;
	char *temp = (char *)malloc(sizeof(char) * strlen(line) + 1);
	char *token;
	char *space;
	t_comm **head = cmd;
	bzero(temp, strlen(line) + 1);

	while (line[i])
	{
		if (is_space(line[i]) || line[i + 1] == '\0')
		{
			if (!is_space(line[i]) && line[i + 1] == '\0') 
                temp[token_index++] = line[i];
			token = find_delimited(temp, cmd);
			if (!process_env_var(&token, cmd, UNQUOTED))
				init_list(cmd, token, STR);
			bzero(temp, strlen(line) + 1);
			token_index = 0;
			free(token);
			i++;
			continue;
		}
		else if (is_squotes(line[i]))
		{
			i = process_squo(line, i, &temp, cmd) + 1;
			if (!line[i])
			{
				init_list(cmd, temp, STR);
				memset(temp, 0, strlen(line));
			}
			token_index = strlen(temp);
			continue;
		}
		else if (is_dquotes(line[i]))
		{
			i = process_dquo(line, i, &temp, cmd) + 1;
			if (!line[i])
			{
				init_list(cmd, temp, STR);
				memset(temp, 0, strlen(line));
			}
			token_index = strlen(temp);
			continue;
		}
		else
			temp[token_index] = line[i];
		token_index++;
		i++;
	}
	print(*head);
}

