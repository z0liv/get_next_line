/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:29:46 by omarquez          #+#    #+#             */
/*   Updated: 2026/05/27 16:02:39 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line_cut;
	char			*concat;
	char			*read_bytes;
	static char		*store;

	read_bytes = malloc(BUFFER_SIZE + 1);
	read(fd, read_bytes, BUFFER_SIZE);
	read_bytes[BUFFER_SIZE] = '\0';
	if (!store)
		store = ft_strdup(read_bytes);
	if(!fd || !read_bytes[0] || !store)
		return (NULL);
	while (read(fd, read_bytes, BUFFER_SIZE) > 0)
	{
		if (ft_strchr(store, '\n'))
		{
			line_cut = ft_get_line(store);
			store = ft_strchr(store, '\n');
		}
		else
		{
			read(fd, read_bytes, BUFFER_SIZE);
			concat = malloc(ft_strlen(store) + ft_strlen(read_bytes) + 1);
			concat = ft_strcat(store, read_bytes);
			store = ft_strdup(concat);
			free(concat);
		}
	}
	line_cut = ft_get_line(store);
	return (line_cut);
}
/* 
recalling the function starts from the frist BS
has to reset the reading to set the bytes already readen
*/
int	main(void)
{
	int	fd;

	fd = open("fd.text", O_RDONLY);
	if(fd == -1)
		return (-1);
	//printf("%s \n", get_next_line(fd));
	//printf("%s \n", get_next_line(fd));
	get_next_line(fd);
	close(fd);
	return (0);
}

