/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:52:31 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/04 13:51:56 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	is_child(int *fd, char *bin, char **args)
{
	close(fd[0]);
	dup2(fd[1], 1);
	if (execve(bin, args, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	is_parent(int *fd, pid_t pid, char **args)
{
	close(fd[1]);
	dup2(fd[0], 0);
	if (waitpid(pid, NULL, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

int	is_pipe(char **arg) 
{
	int	i;

	for(i = 0; arg[i]; i++)
	{
		if (strcmp(arg[i], "|") == 0)
		{
			arg[i] = NULL;
			return i;
		}
	}
	return (0);
}

1. heredoc -> parent
-> third

2. parent process -> builtin + no pipe / do not need fork
	2-1. redirection handling
	2-2. make_args
	2-3. builtin excute
-> first

3. child process -> need to fork
	fork
	3-1. parent_process
		3-1-1. pipe handing
	3-2. child_process
		3-2-1. redirection handling
		3-2-2. pipe handling
		3-2-3. make_args
		3-2-4. excute
			3-2-4-1. builtin
			3-2-4-2. execve	
-> second

signal handling
-> last


// red check -> parent and child
// pipe -> child
	// arg
	parent // built -> parent or child
	child // exec -> child

void	ft_exec(const char *bin, char **args)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		i;

	pid = fork();
	i = 0;
	if (i = is_pipe(args))
		pipe(pipe_fd);
	// if (is_redirect())
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		is_child(pipe_fd, bin, args);
	else
		is_parent(pipe_fd, pid, args);
}
