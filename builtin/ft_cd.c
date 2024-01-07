/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:01:09 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/05 21:22:59 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	ft_cd(char **args) // - ~ / 등 파싱할지 말지 고민
{
	char	*path;
	char	*cwd;
	int		ret;

	path = ft_strdup(args[1]);
	printf("%s\n", path);
	if (chdir(path) == -1)
		perror("chdir");
	free(path);
	return (0);
}
