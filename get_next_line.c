/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:29:46 by omarquez          #+#    #+#             */
/*   Updated: 2026/05/31 10:52:31 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
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

static char	*read_store(int fd, char *store)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	bytes;

	bytes = 1;
	while (!ft_strchr(store, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(store), NULL);
		buffer[bytes] = '\0';
		tmp = ft_strjoin(store, buffer);
		free(store);
		store = tmp;
	}
	return (store);
}

static char	*update_store(char *store, char *line)
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

char	*ft_get_line(char *store)
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
	static char		*store;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_store(fd, store);
	if (!store)
		return (NULL);
	line = ft_get_line(store);
	if (!line)
		return (free(store), store = NULL, NULL);
	store = update_store(store, line);
	return (line);
}
/*
int	main(void)
{
	int	fd;
	char	*result;
	
	fd = open("big_line_no_nl", O_RDONLY);
	if(fd == -1)
		return (-1);
	result = get_next_line(fd);
	printf("%s \n", result);
	char *a,*b,*c,*d,*e,*f;
	a = get_next_line(fd);
	b = get_next_line(fd);
	c = get_next_line(fd);
	d = get_next_line(fd);
	e = get_next_line(fd);
	f = get_next_line(fd);
	printf("%s", a);
	printf("%s", b);
	printf("%s", c);
	printf("%s", d);
	printf("%s", e);
	printf("%s", f);
	free(a);
	free(b);
	free(c);
	free(d);
	free(e);
	free(f);
	
	
	close(fd);
	return (0);
}
*/
