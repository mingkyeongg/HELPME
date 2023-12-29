/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:52:51 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/29 15:35:52 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int main(int argc, char** argv, char **envp)
{
    (void)argc;
    (void)argv;

    execve("/bin/ls", "ls", envp);
	return (0);
}