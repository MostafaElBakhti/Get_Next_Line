/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:45:52 by mel-bakh          #+#    #+#             */
/*   Updated: 2025/11/21 17:31:26 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_line(int fd, char *remainder)
{
    char        *buffer;
    int         readed_bytes;

    buffer = malloc(BUFF_SIZE + 1);
    if (!buffer)
        return (NULL);
    
    readed_bytes = 1;
    while (!ft_strchr(remainder, '\n') && readed_bytes > 0)
    {
        readed_bytes = read(fd, buffer, BUFF_SIZE);

        if (readed_bytes < 0)
        {
            free(buffer);
            free(remainder);
            return (NULL);
        }

        buffer[readed_bytes] = '\0';
    }
    
}

char *get_next_line(int fd)
{
    static char *remainder;
    char        *line;

    if (fd < 0 || BUFF_SIZE <= 0) 
        return (NULL);
    remainder = ft_read_line(fd, remainder);
    
    
}

// ! READ FUNCTION
//? ssize_t read(int fd, void *buf, size_t count);
// ? The read() function attempts to read up to count bytes from file
//? descriptor fd into the buffer starting at buf.