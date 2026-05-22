/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:29:46 by omarquez          #+#    #+#             */
/*   Updated: 2026/05/22 13:41:36 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	char			*line_cut;
	size_t			counter;
	//size_t			size;
	//static int		line_num;

	counter = 0;
	line = malloc(BUFFER_SIZE);
	if(!fd || !line)
	return (NULL);
	read(fd, line, BUFFER_SIZE);
	while(line[counter] != '\n')
		counter ++;
	line_cut = malloc(counter + 1);
	ft_strlcpy(line_cut, line, counter + 1);
	free(line);
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
	printf("%s \n", get_next_line(fd));
	printf("%s \n", get_next_line(fd));
	close(fd);
	return (0);
}

