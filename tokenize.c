/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:33:37 by minkylee          #+#    #+#             */
/*   Updated: 2023/12/29 19:24:03 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

/*


	지금 쿼트 안에 환경변수를 처리하면서 힙-오버플로가 난다.
	"hi my home is'$HOME'" 이런걸 쓰면 나는데 내일 오면 뭐때문인지 확인해볼것!!!!!!!!

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
char *mk_strdup(int start, int end, char *line)
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
        if (!is_space(line[j]))
            new_line[i++] = line[j];
        j++;
    }
    new_line[i] = '\0';  // 새 문자열 끝에 널 종료 문자 추가
    return new_line;
}


char *find_delimited(char *token, t_comm **cmd)
{
    int i = 0;
    int start = i;
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
                new_token = mk_strdup(start, i - 1, token);
				process_env_var(&new_token, cmd);
                init_list(cmd, new_token, STR);
                free(new_token);
            }
			// 파이프 출력
			if (token[i] == '|')
			{
				new_token = mk_strdup(i, i, token);
				init_list(cmd, new_token, PIPE);
				i++;
			}

            // 리다이렉션과 기호 출력
            else if ((token[i] == '<' || token[i] == '>') && token[i + 1] == token[i])
            {
                new_token = mk_strdup(i, i + 1, token);
				if (new_token[0] == '<')
					init_list(cmd, new_token, DLESS);
				else
					init_list(cmd, new_token, DGREAT);
                i += 2;
            }
            else
            {
                new_token = mk_strdup(i, i, token);
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
        new_token = mk_strdup(start, i - 1, token);
	else // 없으면 빈문자열 리턴
		new_token = ft_strdup("");
	return new_token;
}

int process_dquo(char *line, int start, char **temp, t_comm **cmd)
{
    int end = start + 1;
    char *token;
	char *isolation;

	isolation = find_delimited(*temp, cmd);
    while (line[end])
    {
        if (is_dquotes(line[end]))
		{
            token = mk_strdup(start + 1, end - 1, line);
			break;
		}
        end++;
    }
	memset(*temp, 0, strlen(line));
	strcat(*temp, isolation);
	strcat(*temp, token);
	process_env_var(temp, cmd);
    return ft_strlen(token) + 2;
}

int process_squo(char *line, int start, char **temp, t_comm **cmd)
{
    int end = start + 1;
    char *token;
	char *isolation;

	isolation = find_delimited(*temp, cmd);
    while (line[end])
    {
        if (is_squotes(line[end]))
		{
            token = mk_strdup(start + 1, end - 1, line);
			break;
		}
        end++;
    }
	memset(*temp, 0, strlen(line));
	strcat(*temp, isolation);
	strcat(*temp, token);
    return ft_strlen(token) + 2;
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

/* 문자를 나눠용 */
void split_line(char *line, t_comm **cmd)
{
	int i = 0;
	int token_index = 0;
	char *quote_temp;
	char *temp = (char *)malloc(sizeof(char) * strlen(line) + 1);
	char *token;
	t_comm **head = cmd;
	bzero(temp, strlen(line) + 1);

	while (line[i])
	{
		if (is_space(line[i]) || line[i + 1] == '\0')
		{
			if (!is_space(line[i]) && line[i + 1] == '\0') 
                temp[token_index++] = line[i];
			token = find_delimited(temp, cmd);
			process_env_var(&token, cmd);
			bzero(temp, strlen(line) + 1);
			token_index = 0;
			init_list(cmd, token, STR);
			free(token);
			i++;
			continue;
		}
		else if (is_squotes(line[i]))
		{
			i += process_squo(line, i, &temp, cmd);
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
			i += process_dquo(line, i, &temp, cmd);
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

/* 환경변수 값을 대치합니다.*/
void process_env_var(char **token, t_comm **cmd)
{
    char *var_name;
	char *var_value;
	char *new_token;
    int start = 0;

    char *dollar_pos = strchr(*token, '$');
    if (dollar_pos == NULL) 
		return; // '$' 없으면 종료
	if (!check_dgreat(*cmd)) // 만약 직전 토큰이 DGREAT라면
		return;

    var_name = dollar_pos + 1;
    var_value = getenv(var_name); // 환경변수 값 찾기

    if (var_value)
	{
        // 환경변수 값으로 대체
        *dollar_pos = '\0'; // '$' 앞부분 잘라내기
        new_token = (char *)malloc(strlen(*token) + strlen(var_value) + strlen(dollar_pos + strlen(var_name) + 1) + 1);
        if (new_token) 
		{
            strcpy(new_token, *token); // '$' 앞부분 복사
            strcat(new_token, var_value); // 환경변수 값 추가
            strcat(new_token, dollar_pos + strlen(var_name) + 1); // 환경변수 이름 이후 부분 추가
            free(*token); // 원래 토큰 메모리 해제
            *token = new_token; // 새 토큰으로 업데이트
        }
    }
}
