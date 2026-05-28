/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:29:40 by omarquez          #+#    #+#             */
/*   Updated: 2026/05/28 15:05:39 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	if (!str)
		return (0);
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

	if (!s)
		return (NULL);
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
	if (src)
	{
		if (size > 0)
		{
			while (count < (size - 1) && src[count])
			{
				dst[count] = src[count];
				count ++;
			}
			dst[count] = '\0';
		}
	}
	return (src_len);
}
char	*ft_strchr(const char *s, int c)
{
	const char	*temp_str;
	size_t			counter;

	if (!s)
		return (NULL);
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
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	size;
	size_t	counter;

	counter = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	dest = (char *) malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	while (counter < len)
	{
		dest[counter] = s[start + counter];
		counter ++;
	}
	dest[counter] = '\0';
	return (dest);
}
