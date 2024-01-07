/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:31:34 by seokjyan          #+#    #+#             */
/*   Updated: 2024/01/05 17:07:08 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv, char **envp)
{
	int	i;
    char *env_var_name = "TERM_PROGRAM";
    char *env_var_value = getenv(env_var_name);

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
    return (0);
}
