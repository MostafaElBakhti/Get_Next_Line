/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:21:00 by mel-bakh          #+#    #+#             */
/*   Updated: 2025/11/23 21:55:58 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strchr(const char *s, int c)
{
	int i;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

size_t ft_strlen(const char *s1)
{
	size_t len;
	if (!s1)
		return (0);

	len = 0;
	while (s1[len])
	{
		len++;
	}
	return len;
}
char *ft_strcat(char *dst, char *src)
{
	size_t d_len;
	size_t i;

	d_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (dst);
}
char *ft_strcpy(char *dst, const char *src)
{
	size_t i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return dst;
}

char *ft_strjoin(char *s1, char *s2)
{
	char *new;
	size_t s1_len;
	size_t s2_len;
	size_t i;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = calloc(1, 1);

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);

	new = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	ft_strcpy(new, s1);
	ft_strcpy(new + s1_len, s2);
	free(s1);
	return (new);
}