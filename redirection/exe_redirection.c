/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:56:32 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/11 15:51:30 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	ft_redirection_out(char *arg, int type)
{
	int	fd;

	if (type == GREAT)
	{
		fd = open(arg, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			return (EXIT_FAILURE);
		}
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
	dup2(fd, 1);
	close(fd);
	return (EXIT_SUCCESS);
}

int	ft_redirection_in(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
	return (EXIT_SUCCESS);
}

void	exe_redirection(char *arg, int type)
{
	if (type == GREAT || type == DGREAT)
		ft_redirection_out(arg, type);
	if (type == LESS)
		ft_redirection_in(arg);
	// if (type == DLESS)
		// ft_here_document();
}
