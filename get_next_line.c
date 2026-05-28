/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omarquez <omarquez@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 15:29:46 by omarquez          #+#    #+#             */
/*   Updated: 2026/05/28 15:55:51 by omarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	counter;

	s1_len = ft_strlen(s1);
	counter = 0;
	if (!s1)
		s1 = ft_strdup("");
	dest = malloc(s1_len + ft_strlen(s2) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, ft_strlen(s1) + 1);
	while(s2[counter])
	{
		dest[s1_len + counter] = s2[counter];
		counter ++;
	}
	dest[s1_len + counter] = '\0';

	free(s1);
	return (dest);
}


char	*ft_get_line(char *store)
{
	size_t		counter;

	counter = 0;
	if (!store || !store[0])
		return (NULL);
	while(store[counter] && store[counter] != '\n')
		counter ++;
	if(store[counter] == '\n')
		counter ++;
	return (ft_substr(store, 0, counter));
}

char	*get_next_line(int fd)
{
	char			*line;
	char			data[BUFFER_SIZE + 1];
	char			*tmp_store;
	ssize_t			read_bytes;
	static char		*store;

	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(store, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, data, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		data[read_bytes] = '\0';
		store = ft_strjoin(store, data);
	}
	line = ft_get_line(store);
	tmp_store = ft_substr(store, ft_strlen(line), read_bytes);
	free(store);
	store = tmp_store;
	return (line);
}

/*
line = ft_get_line(store);
tmp_store = ft_substr(store, ft_strlen(line), read_bytes);
free(store);
store = malloc(ft_strlen(tmp_store) + 1);
ft_strlcpy(store, tmp_store, ft_strlen(tmp_store) + 1);
free(tmp_store); 
return (line);
*/

/*
int	main(void)
{
	int	fd;
	char *a,*b,*c,*d,*e,*f;

	fd = open("fd.text", O_RDONLY);
	if(fd == -1)
		return (-1);
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
