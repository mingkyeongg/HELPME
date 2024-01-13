/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:34:09 by minkylee          #+#    #+#             */
/*   Updated: 2024/01/12 17:12:39 by minkylee         ###   ########.fr       */
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

void check_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_comm	*cmd;
	t_envp	*my_envp;
	t_data	*ofd_arg;

	my_envp = make_envp(envp);
	while (1)
	{
		cmd = malloc(sizeof(t_comm));
		ofd_arg = malloc(sizeof(t_data));
		cmd = NULL;

		if (!read_input(&cmd, my_envp))
			continue ;
		ofd_and_arg->in_fd = dup(0);
		ofd_and_arg->out_fd = dup(1);
		cmd = ft_redirect_handling(cmd);
		args = make_args(cmd, &args_cnt);
		if (is_blt(args))
			exe_cmd(my_envp, args, args_cnt);
		free_list(cmd);
		dup2(ofd_and_arg->in_fd, 0);
		dup2(ofd_and_arg->out_fd, 1);
	}
	atexit(check_leaks);
}
