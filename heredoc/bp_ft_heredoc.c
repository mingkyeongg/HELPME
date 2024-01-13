/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bp_ft_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:49:57 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/13 22:47:14 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	is_delimiter(char *input, char *delimiter)
{
	int	i;

	if (!delimiter)
		return (1);
	i = 0;
	printf("same %d\n", ft_strcmp(input, delimiter));
	if (ft_strcmp(input, delimiter) == 0)
		return (0);
	// while (input[i] != '\0' && delimiter[i] != '\0')
	// {
	// 	printf("input[%d] = %c, delimiter[%d] = %c\n", i, input[i], i, delimiter[i]);
	// 	if (input[i] != delimiter[i])
	// 		return (0);
	// 	i++;
	// }
	// if (!(input[i] == '\0' && delimiter[i] == '\0'))
	// 	return (1);
	return (1);
}

char	*set_file_name(void)
{
	int		i;
	char	*num;
	char	*tmp;
	char	*file_name;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		file_name = ft_strjoin(tmp, num);
		free(num);
		if (access(file_name, F_OK) != 0)
			break ;
		free(file_name);
		i++;
	}
	return (file_name);
}

t_comm	*set_fd(t_comm *cmd)
{
	t_comm	*cp_cmd;
	char	*tmp;

	cp_cmd = cmd;
	while (cp_cmd != NULL)
	{	
		if (cp_cmd->type == DLESS)
		{
			cp_cmd->hdoc = (t_hdoc *)malloc(sizeof(t_hdoc *));
			tmp = set_file_name();
			cp_cmd->hdoc->in_fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
			cp_cmd->hdoc->filename = tmp;
			cp_cmd->hdoc->delimiter = cp_cmd->next->token;
			close(cp_cmd->hdoc->in_fd);
		}
		cp_cmd = cp_cmd->next;
	}
	return (cmd);
}

void	read_heredoc(char *file_name, char *delimiter)
{
	char	*input;
	int		file_fd;

	file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (is_delimiter(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, file_fd);
		free(input);
	}
	close(file_fd);
}

int	is_heredoc(t_comm *cmd)
{
	t_comm	*cp_cmd;
	int		cnt;

	cp_cmd = cmd;
	cnt = 0;
	while (cp_cmd != NULL)
	{
		if (cp_cmd->type == DLESS)
			cnt++;
		cp_cmd = cp_cmd->next;
	}
	return (cnt);
}

void	fork_read_heredoc(t_comm *cmd)
{
	t_comm	*cp_cmd;
	int		status;

	if (fork() == 0)
	{
		cp_cmd = cmd;
		while (cp_cmd != NULL)
		{
			if (cp_cmd->type == DLESS)
				read_heredoc(cmd->hdoc->filename, cmd->hdoc->delimiter);
		}
		cp_cmd = cp_cmd->next;
	}
	waitpid(-1, &status, 0);
	exit(0);
}

int	ft_heredoc(t_comm *cmd)
{
	int	cnt_dless;

	cnt_dless = is_heredoc(cmd);
	if (cnt_dless == 0)
		return (cnt_dless);
	cmd = set_fd(cmd);
	fork_read_heredoc(cmd);
	return (cnt_dless);
}
