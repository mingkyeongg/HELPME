/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:31:34 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/29 15:23:10 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    char *command = argv[1];
    char *path = find_cmd_path(command);
    if (path != NULL) {
        printf("Path for %s: %s\n", command, path);
        free(path);
    } else {
        printf("Command %s not found\n", command);
    }
    return 0;
}
