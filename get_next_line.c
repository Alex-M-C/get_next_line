/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <aleconst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:51:29 by aleconst          #+#    #+#             */
/*   Updated: 2025/02/19 14:01:34 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static char	*process_buf(char *buf, int buf_size, int fd);
static char	*add_buf(char *buf);
static void	*ft_calloc(size_t nmemb, size_t size);

/*
Allocates memory for an array of NMEMB elements of SIZE bytes each.
@return A pointer to the allocated memory.
*/
static void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = nmemb * size;
	if (nmemb != 0 && size != 0 && total_size / size != nmemb)
		return ((void *)0);
	ptr = malloc(total_size);
	if (!ptr)
		return ((void *)0);
	while (total_size > 0)
	{
		((unsigned char *)ptr)[total_size - 1] = 0;
		total_size--;
	}
	return (ptr);
}

/*
Appends the SRC string to the DEST string.
@attention Both strings must be NULL-terminated and must not overlap
@returns The total length of the string it tried to create or the length
needed if the DEST size is not enough to concatenate SRC
*/
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	counter;
	size_t	dest_end;

	counter = 0;
	dest_end = ft_strlen(dest);
	if (size <= dest_end)
	{
		return (size + ft_strlen(src));
	}
	while (src[counter] != '\0' && (dest_end + counter) < size - 1)
	{
		dest[dest_end + counter] = src[counter];
		counter++;
	}
	dest[dest_end + counter] = '\0';
	return (dest_end + ft_strlen(src));
}

static char	*process_buf(char *buf, int buf_size, int fd)
{
	char	*line;
	char	*temp;
	ssize_t	br;

	line = ft_strchr(buf, '\n');
	if (!line)
	{
		line = add_buf(buf);
		br = read(fd, buf, buf_size);
		if (br <= 0)
			return (buf[0] = '\0', line);
		return (buf[br] = '\0', process_buf(buf, buf_size, fd));
	}
	temp = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(line) + 1);
	if (!temp)
		return (NULL);
	ft_memmove(buf, line + 1, ft_strlen(line) + ft_strlen(temp));
	line = add_buf(temp);
	free(temp);
	return (line);
}

static char	*add_buf(char *buf)
{
	static char	*cpy_line = NULL;
	char		*temp;
	int			i;

	i = 0;
	temp = NULL;
	if (cpy_line && cpy_line[ft_strlen(cpy_line) - 1] == '\n')
		free(cpy_line);
	else if (cpy_line)
	{
		temp = cpy_line;
		i += ft_strlen(cpy_line);
	}
	cpy_line = (char *)ft_calloc((i + ft_strlen(buf) + 1), sizeof(char));
	if (!cpy_line)
		return ((void *)0);
	if (temp)
	{
		ft_memmove(cpy_line, temp, ft_strlen(temp) + ft_strlen(cpy_line) + 1);
		free(temp);
	}
	if (buf)
		ft_strlcat(cpy_line, buf, ft_strlen(buf) + ft_strlen(cpy_line) + 1);
	return (ft_strdup(cpy_line));
}

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE] = {0};
	char			*line;
	ssize_t			nl;

	line = (void *)0;
	if (buf[0] && ft_strlen(buf) > 0)
	{
		line = process_buf(buf, BUFFER_SIZE, fd);
		if (!line)
			return ((void *)0);
	}
	else
	{
		nl = read(fd, buf, sizeof(buf));
		if (nl <= 0)
			return ((void *)0);
		line = process_buf(buf, BUFFER_SIZE, fd);
		if (!line)
			return ((void *)0);
	}
	return (line);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test2.txt", O_RDONLY | O_CREAT, 777);
/* 	line = get_next_line(fd);

	if (line)
	{
		printf("%s\n", line);
	}
 */
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	//free(line);
	close(fd);
}
