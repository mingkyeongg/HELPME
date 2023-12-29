#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *cmd[] = {"ls", "-la", NULL};

    execve("/bin/ls", cmd, envp);
}

while (list != NULL)
{
    cnt_pipe();

    if (is_it_builtin && pipe_cnt == 0)
        parant_process;
    else
        child_process;

    make_args(); -> flg 가 pipe 이전까지
    
    while (list->flg != PIPE || list != NULL)
    {
        if (list->flg == LESS) // <
            less_handling(); list.token = < / list->next.token = filename
            free(list.token);
            free(list->next.token);
            list.token = NULL;
            list->next.token = NULL;
            list.flgs = STR;
            list->next.flgs = STR;
        else if (list->flg == DLESS) // <<
            dless_handling();
        else if (list->flg == GRATE) // >
            grate_handling();
        else if (list->flg == DGRATE) // >>
            dgrate_handling();
        list = list->next;
    }
    while (list->fl)
}

list->token = "asdf asdf ";
list->token = NULL;

1. args 생성

path_find -> 던져주기 전 과정

1. 빌트인인지 찾는거
2. 파이프 존재하는지 찾는거
3. 위의 경우에 따라 parent 인지 child 인지 판단
4. 리다이렉션 

<a < v < d < d echo str < d < f < g ls ls