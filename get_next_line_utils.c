/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:29:40 by omarquez          #+#    #+#             */
/*   Updated: 2026/05/27 15:37:01 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (*str != '\0')
	{
		counter ++;
		str ++;
	}
	return (counter);
}

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*dest;

	s_len = ft_strlen(s) + 1;
	dest = malloc(s_len);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, s_len);
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		count;
	size_t		src_len;

	count = 0;
	src_len = ft_strlen(src);
	if (size > 0)
	{
		while (count < (size - 1) && src[count])
		{
			dst[count] = src[count];
			count ++;
		}
		dst[count] = '\0';
	}
	return (src_len);
}
char	*ft_strchr(const char *s, int c)
{
	const char	*temp_str;
	int			counter;

	temp_str = (const char *) s;
	counter = 0;
	while (c > 256)
		c = c - 256;
	while (temp_str[counter] != '\0')
	{
		if (temp_str[counter] == c)
			return ((char *) &temp_str[counter]);
		counter ++;
	}
	if (temp_str[counter] == c)
		return ((char *) &temp_str[counter]);
	return (NULL);
}
char	*ft_strcat(char *dst, char *src)
{
	size_t	dst_len;
	size_t	counter;

	dst_len = ft_strlen(dst);
	counter = 0;
	while (src[counter])
	{
		dst[dst_len + counter] = src[counter];
		counter ++;
	}
	dst[dst_len + counter] = '\0';
	return (dst);
}

char	*ft_get_line(char *read_bytes)
{
	char	*line_cut;
	int		counter;

	counter = 0;
	if (!read_bytes)
		return (NULL);
	while(read_bytes[counter] != '\n')
		counter ++;
	if(read_bytes[counter] == '\n')
	{
		line_cut = malloc(counter + 1);
		if (!line_cut)
			return (NULL);
		ft_strlcpy(line_cut, read_bytes, counter + 1);
		return (line_cut);
	}
	return (NULL);
}
