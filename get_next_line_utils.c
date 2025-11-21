/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-bakh <mel-bakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:21:00 by mel-bakh          #+#    #+#             */
/*   Updated: 2025/11/21 19:26:42 by mel-bakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "get_next_line.h"

char *strchr(const char *s, int c)
{
	int i;
	i = 0 ;
	if(!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

size_t ft_strlen(char *s1)
{
	size_t	len;
	if (!s1)
		return (0);
	
	len = 0; 
	while (s1[len])
	{
		len++;
	}
	return len;
}
char	*ft_strcat(char *dst, char *src)
{
	size_t	d_len;
	size_t	i;

	d_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = 0;
	return (dst);
}

char *ft_strjoin(char *s1, char *s2)
{	
	char 	*ptr;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (!s2)
		return (NULL);
	
	s2_len = ft_strlen(s2);
	s1_len = ft_strlen(s1);
	
	ptr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ptr)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while ( i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	free(s1);
	ptr[i] = 0 ;
	ptr = ft_strcat(ptr, s2);
	return (ptr);
}