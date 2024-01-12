#include "minishell.h"

// exec 관련 함수는 프로세스의 주변 환경(파일 디스크립터 정보, 시그널 처리 방법) 은 그대로 유지한 채 세그먼트 영역만 교체
// 리다이렉트가 적용한 파일 디스크립터는 내가 적용한 환경에서 새로운 프로세스가 실행이 되도록 구성


int is_pipe(char **arg)   // 명령어 줄에 파이프 존재 여부를 조사하는 함수 구현
{
	int i;

	for(i = 0; arg[i]; i++)
	{
		if (strcmp(arg[i], "|") == 0)
		{
			arg[i] = NULL;
			return i;   // 파이프의 위치 반환
		}
	}
	return 0;
}
int is_background(char **arg)
{
	int i;

	for (i = 0; arg[i]; i++)
	{
		if(!strcmp(arg[i], "&"))
		{
			arg[i] = NULL;
			return 1;
		}
	}
	return 0;
}

void exec_command(char **arg) // 입력값을 받아 명령과 옵션을 분리해서 전달한다. 외부 명령
{
	pid_t	pid;
	int		pd[2];
	int		background_flag = 0;
	int		index;

	if(is_background(arg))
		background_flag = 1;

	switch (pid=fork())
	{
	case -1:				//failure
		perror("fork");
		return;
		break;
	case 0:				// child process 외부 명령을 수행한다.
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL); // 자식 프로세스에서는 시그널을 디폴트로 회복

		if (index==is_pipe(arg))
		{
			pipe(pd);
			switch(fork())
			{
				case -1:
					perror("fork in pipe");
					return ;
				case 0:
					close(pd[0]);  // 입력 디스크립터
					dup2(pd[1], 1);  // 표준 출력과 pipe의 write 디스크립터 중첩
					execvp(arg[0], arg);  // pipe 앞쪽 명령어 수행
					perror("execvp");
					exit(1);
					break;
				default:
					close(pd[1]);
					dup2(pd[0], 0);   // 입력과 read 디스크립터 중첩
					execvp(arg[index + 1], &arg[index + 1]);  // 파이프 뒤쪽 명령어 수행
					perror("execvp");
					exit(1);
					break;
			}
		}
		else
		{
			redirectin(arg);  // 리턴값을 이용해서 오류를 점검한다던가 처리하는게 좋음
			redirectout(arg);
			redirecterr(arg);
			execvp(arg[0], arg);			// 명령어가 얼마나 들어올지 몰라서 v, 경로를 따라가야 하기 때문에 p
			perror("execvp");				// 실패경우
			exit(1);
			break;
		}
	default:							//부모 프로세스
		if(background_flag == 0)
			waitpid(pid, NULL, 0);
		break;
	}
}