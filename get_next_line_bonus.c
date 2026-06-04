/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:29:46 by omarquez          #+#    #+#             */
/*   Updated: 2026/06/04 11:47:42 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;
	size_t	counter;

	counter = 0;
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = malloc(s1_len + s2_len + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, s1_len + 1);
	while (counter < s2_len)
	{
		dest[s1_len + counter] = s2[counter];
		counter ++;
	}
	dest[s1_len + counter] = '\0';
	return (dest);
}

static char	*ft_read_store(int fd, char *store)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes;

	bytes = 1;
	while (!ft_strchr(store, '\n') && bytes > 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (free(store), NULL);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(store), NULL);
		buffer[bytes] = '\0';
		tmp = ft_strjoin(store, buffer);
		free(store);
		store = tmp;
		free(buffer);
	}
	return (store);
}

static char	*ft_update_store(char *store, char *line)
{
	char	*new_store;

	new_store = ft_substr(
			store,
			ft_strlen(line),
			ft_strlen(store) - ft_strlen(line)
			);
	free(store);
	return (new_store);
}

static char	*ft_get_line(char *store)
{
	size_t		counter;

	counter = 0;
	if (!store || !store[0])
		return (NULL);
	while (store[counter] && store[counter] != '\n')
		counter ++;
	if (store[counter] == '\n')
		counter ++;
	return (ft_substr(store, 0, counter));
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*store[FD_SIZE];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = ft_read_store(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	line = ft_get_line(store[fd]);
	if (!line)
		return (free(store[fd]), store[fd] = NULL, NULL);
	store[fd] = ft_update_store(store[fd], line);
	return (line);
}

/*
#include <stdio.h>
int	main(void)
{
	int		counter;
	int		fds[3];
	char	*line;
	
	counter = 0;
	fds[0] = open("text1.txt", O_RDONLY);
	fds[1] = open("text2.txt", O_RDONLY);
	fds[2] = open("text3.txt", O_RDONLY);
	if(fds[0] == -1 || fds[1] == -1 || fds[2] == -1)
		return (-1);
	printf("%d %d %d \n", fds[0], fds[1], fds[2]);
	
	while(counter < 3)
	{
		while((line = get_next_line(fds[counter])))
		{
			printf("%s", line);
			free(line);
		}
		counter ++;
	}
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	return (0);
}
*/
