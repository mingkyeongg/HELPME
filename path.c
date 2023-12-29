/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:23:13 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/29 17:01:20 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_strtok(char *str, char sepa)
{
	static char	*stock = NULL;
	char		*ptr;
	int			i;

	i = 0;
	ptr = NULL;
	if (str != NULL)
		stock = strdup(str);
	while (*stock != '\0')
	{
		if (i == 0 && *stock != sepa)
		{
			i = 1;
			ptr = stock;
		}
		else if (i == 1 && *stock == sepa)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	return (ptr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	i = 0;
	while (i < n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dst);
}

char	*path_strjoin(char const	*s1, char const	*s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, s1_len);
	ft_memcpy(res + s1_len, "/", 1);
	ft_memcpy(res + s1_len + 1, s2, s2_len);
	res[s1_len + s2_len + 1] = 0;
	return (res);
}

char	*make_cmd_path(char *path_copy, char *token, char *command)
{
	char	*full_path;

	while (token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}
		full_path = path_strjoin(token, command);
		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = ft_strtok(NULL, ':');
	}
	return (NULL);
}

char	*find_cmd_path(char *command)
{
	char	*path;
	char	*path_copy;
	char	*token;
	char	*res;

	path = getenv("PATH");
	if (!path)
	{
		perror("getenv");
		return (NULL);
	}
	path_copy = strdup(path);
	if (!path_copy)
	{
		perror("strdup");
		return (NULL);
	}
	token = ft_strtok(path_copy, ':');
	res = make_cmd_path(path_copy, token, command);
	return (res);
}
