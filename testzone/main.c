/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:31:34 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/12 15:32:55 by seokjyan         ###   ########.fr       */
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

void	args_bye(char **args)
{
	args[0] = "bye1";
	args[1] = "bye2";
	args[2] = "bye3";
	args[3] = "bye4";
	args[4] = "bye5";
	args[5] = "bye6";
}

int main() {
	char **args;

	args = (char **)malloc(sizeof(char *) * 7);
	args[0] = (char *)malloc(sizeof(char) * 10);
	args[1] = (char *)malloc(sizeof(char) * 10);
	args[2] = (char *)malloc(sizeof(char) * 10);
	args[3] = (char *)malloc(sizeof(char) * 10);
	args[4] = (char *)malloc(sizeof(char) * 10);
	args[5] = (char *)malloc(sizeof(char) * 10);
	args[6] = NULL;
	args[0] = "hello1";
	args[1] = "hello2";
	args[2] = "hello3";
	args[3] = "hello4";
	args[4] = "hello5";
	args[5] = "hello6";
	int i = 0;
	while (args[i] != NULL)
	{
		printf("%s\n", args[i]);
		i++;
	}
	args_bye(args);
	i = 0;
	while (args[i] != NULL)
	{
		printf("%s\n", args[i]);
		i++;
	}
}
