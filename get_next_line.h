/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:29:57 by mel-bakh          #+#    #+#             */
/*   Updated: 2025/11/23 00:50:23 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char    *get_next_line(int fd);

char    *ft_strchr(const char *s, int c);
size_t   ft_strlen(const char *s);
char    *ft_strcat(char *dst, char *src);
char    *ft_strjoin(char *s1, char *s2);

char    *ft_read_line(int fd, char *remainder);
char    *extract_line(char *remainder);
char    *update_remainder(char *remainder);

#endif
