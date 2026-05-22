/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:29:40 by omarquez          #+#    #+#             */
/*   Updated: 2026/05/22 12:59:39 by omarquez         ###   ########.fr       */
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
