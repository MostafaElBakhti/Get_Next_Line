/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:20:25 by mel-bakh          #+#    #+#             */
/*   Updated: 2025/11/26 03:27:46 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("test.html", O_RDONLY);

    if (fd < 0)
    {
        printf("failed");
    }
    int i = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("line %d : %s", i, line);
        i++;
        free(line);
    }

    close(fd);
}