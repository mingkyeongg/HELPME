/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:31:34 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/10 18:15:53 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_redirection_out(char *arg, int type)
{
	int	fd;

	if (type == 2)
	{
		fd = open(arg, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			return (EXIT_FAILURE);
		}
	printf("type = 1%d\n", type);
	}
	else
	{
		fd = open(arg, O_WRONLY|O_CREAT|O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			return (EXIT_FAILURE);
		}
	}
	printf("type = 2%d\n", type);
	dup2(fd, 1);
	printf("type = 3%d\n", type);
	close(fd);
	return (EXIT_SUCCESS);
}

void create_test_file(const char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    const char *text = "This is a test file.\nFeel free to add more content!";
    ssize_t bytes_written = write(fd, text, strlen(text));
    if (bytes_written == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main() {
    const char *test_filename = "test_file.txt";
    
    // 예제 파일 생성
    create_test_file(test_filename);

    // ft_redirection_out 함수를 사용하여 파일에 출력 리다이렉션
    if (ft_redirection_out(test_filename, 1) == EXIT_FAILURE) {
        fprintf(stderr, "Error redirecting output\n");
        exit(EXIT_FAILURE);
    }

    // 이제 표준 출력은 test_file.txt로 리다이렉션됩니다.
    printf("This is redirected output.\n");

    return 0;
}
