/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:34:09 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/10 20:59:18 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"


/*
	미니쉘 구현 계획
	1. 토큰 분리 규칙에 따라서 나누기
*/


/*
	S : 개행, 스페이스
	A : 일반 문자
	P : 파이프
	Q : 더블쿼트
	q : 싱글쿼트
	r : 리다이렉트 >
	D : 달러표시
	s : 문자열
*/

int main(int argc, char **argv, char **envp)
{
	t_comm *cmd;
	t_envp *my_envp;
	char	**args;
	int		args_cnt;

	my_envp = make_envp(envp);
	// print_my_envp(my_envp); // 출력용
	while(1)
	{
		cmd = malloc(sizeof(t_comm));
		cmd = NULL;
		if (!read_input(&cmd))
			continue;
		args = make_args(cmd, &args_cnt);
		// print_args(args); // 출력용
		// printf("%d\n", is_blt(args));
		if (is_blt(args))
			exe_cmd(my_envp, args, args_cnt);
		free_list(cmd);
	}
}