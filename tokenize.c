/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:33:37 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/05 18:40:41 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

/*


	문제
	1. 엔터만 치면 터져버림 ㅠㅠㅠ
	
*/

void print(t_comm *cmd)
{
	while (cmd)
	{
		printf("token : %s             type : %d      length : %d\n", cmd->token, cmd->type, cmd->length);
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
        exit(1);

    i = 0;  // 새 문자열의 인덱스
    j = start;  // 원본 문자열의 인덱스
    while (j <= end)
	{
        if (line[j] == '\0') 
            break;  // 원본 문자열의 끝에 도달
        if (!is_space(line[j]) && flag == REMOVE)
            new_line[i++] = line[j];
		else if (flag == LEAVE)
			new_line[i++] = line[j];
        j++;
    }
    new_line[i] = '\0';  // 새 문자열 끝에 널 종료 문자 추가
	return new_line;
}

int prev_check(t_comm **cmd, char *token, int type)
{
	char *new_token;

	if (*cmd == NULL)
		return 1;
	t_comm *temp = *cmd;
	while (temp -> next)
		temp = temp->next;
	if (temp->type == CONTINUE)
	{
		new_token = ft_strjoin(temp->token, token);
		free(temp->token);
		temp->token = new_token;
		temp->type = type;
		temp->length += ft_strlen(token);
		return 0;
	}
	return 1;
}

void push_back(t_comm **cmd, char *token, int type)
{
	if (!token || token[0] == '\0')
		return;
	if (!prev_check(cmd, token, type))
		return;
    t_comm *push = (t_comm *)malloc(sizeof(t_comm));
    if (!push) 
		exit(1);
    push->token = ft_strdup(token);
    push->length = ft_strlen(token);
    push->type = type;
    push->next = NULL;
    if (*cmd == NULL)
        *cmd = push;
    else
	{
        t_comm *temp = *cmd;
        while (temp->next)
            temp = temp->next;
        temp->next = push;
    }
}

void split_line(char *line, t_comm **cmd)
{
	int i = 0;
	int start = 0;
	char *temp;
 
	while (line[i])
	{
		if (line[i + 1] == '\0' || is_space(line[i]))
		{
			temp = find_delimited(mk_strdup(start, i, line, REMOVE), cmd, 0, 0);
			process_env_var(&temp, cmd, UNQUOTED, line);
			push_back(cmd, temp, STR);
			free(temp);
			start = i + 1;
		}
		else if(is_squotes(line[i]) || is_dquotes(line[i]))
			process_in_quotes(line, &i, &start, cmd);
		i++;
	}
	print(*cmd);
}
