/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_synerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:46:49 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/07 12:06:32 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int found_squote_err(char *buf)
{
	int i;
	int quote_flag;

	i = 0;
	quote_flag = 0;
	while (buf[i])
	{
		if (!quote_flag && buf[i] == 'q')
			quote_flag = 1;
		else if (quote_flag && buf[i] == 'q')
			quote_flag = 0;
		i++;
	}
	if (quote_flag)
	{
		printf("minishell: syntax error near unexpected token '\n");
		return 0;
	}
	return 1;
}

int found_dquote_err(char *buf)
{
	int i;
	int quote_flag;

	i = 0;
	quote_flag = 0;
	while (buf[i])
	{
		if (!quote_flag && buf[i] == 'Q')
			quote_flag = 1;
		else if (quote_flag && buf[i] == 'Q')
			quote_flag = 0;
		i++;
	}
	if (quote_flag)
	{
		printf("minishell: syntax error near unexpected token \"\n");
		return 0;
	}
	return 1;
}

int pipe_at_the_end(char *buf)
{
	int i;

	i = ft_strlen(buf) - 1;
	while (i >= 0 && buf[i] == 'S')
		i--;
	if (i > 0 && buf[i] == 'p')
	{
		if ((i >= 1 && buf[i] == 'p' && buf[i - 1] != 'p'))
			printf("minishell: syntax error near unexpected token `|'\n");
		else if (buf[i - 1] == 'p')
			printf("minishell: syntax error near unexpected token `||'\n");
		return 0;
	}
	else if (i == 0 && buf[i] == 'p')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return 0;
	}
	return 1;
}

int only_redirec(char *buf)
{
    int i;
    int redirection_found = 0; // 리다이렉션 기호가 발견되었는지 추적합니다.

    i = 0;
    while (buf[i])
    {
        if (buf[i] == '>' || buf[i] == '<')
            redirection_found = 1; // 리다이렉션 기호를 발견했습니다.
        else if (buf[i] != ' ') // 공백이 아닌 다른 문자를 발견하면 0을 반환합니다.
            return 0;
        i++;
    }
    if (redirection_found) { // 리다이렉션 기호가 하나라도 있으면 오류 메시지를 출력하고 1을 반환합니다.
        printf("minishell: syntax error near unexpected token `newline'\n");
        return 1;
    }
    // 모든 문자가 공백인 경우 (즉, 리다이렉션 기호가 없는 경우) 0을 반환합니다.
    return 0;
}


int find_syntax_err(char *buf)
{
	int status;

    if (!pipe_at_the_end(buf) || only_redirec(buf))
	{
        pid_t pid; // 자식 프로세스 생성

		pid = fork();
        if (pid == 0)
            exit(128);  // 종료 코드 128로 종료
        else if (pid > 0)
            waitpid(pid, &status, 0);  // 자식 프로세스 종료 대기
        else
            perror("fork failed");
        return 0;
    }
    return 1;
}
