/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:51:29 by aleconst          #+#    #+#             */
/*   Updated: 2025/01/23 15:51:40 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static char	*process_buf(char buf[], int buf_size);
static char	*add_buf(char *buf, int clear);

static char	*process_buf(char buf[], int buf_size)
{
	char	*line;
	char	*temp;

	line = ft_strchr(buf, '\n');
	if (!line)
	{
		line = add_buf(buf, 1);
		while (buf_size >= 0)
		{
			buf[buf_size--] = 0;
		}
	}
	else
	{
		temp = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(line) + 1);
		if (!temp)
			return (NULL);
		ft_memmove(buf, line + 1, ft_strlen(line));
		ft_memmove(line, temp, ft_strlen(temp) + 1);
	}
	return (line);
}

static char	*add_buf(char *buf, int clear)
{
	static char	*cpy_line = NULL;
	char		*temp;
	int			i;

	i = 0;
	temp = NULL;
	if (clear == 0)
	{
		cpy_line = NULL;
		return ((void *)0);
	}
	if (cpy_line)
	{
		temp = cpy_line;
		i += ft_strlen(cpy_line);
	}
	cpy_line = (char *)malloc((i + ft_strlen(buf) + 1) * sizeof(char));
	if (!cpy_line)
		return ((void *)0);
	if (temp)
		ft_memmove(cpy_line, temp, ft_strlen(temp));
	if (buf)
		ft_memmove(cpy_line, buf, ft_strlen(buf));
	return (cpy_line);
}

/* 	
	nl = read(fd, buf, sizeof(buf));
	if (nl <= 0)
		return ((void *)0);
	while (nl > 0)
	{
		line = add_buf(buf);
		if (!line)
			return ((void *)0);
		nl = read(fd, buf, sizeof(buf));
	} 
*/
// buf = [H, o, l, a, \n, \n, t, r, e, s, \n]
char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE] = {0};
	char			*line;
	ssize_t			nl;

	printf("BUF: %s", buf);
	if (buf[0] && ft_strlen(buf) > 0)
	{
		line = process_buf(buf, BUFFER_SIZE);
	}
	else
	{
		nl = read(fd, buf, sizeof(buf));
		if (nl <= 0)
			return ((void *)0);
		line = process_buf(buf, BUFFER_SIZE);
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

	fd = open("test.txt", O_RDONLY | O_CREAT);
	line = get_next_line(fd);
/* 	
	if (line)
	{
		printf("%s\n", line);
	}
 */
	
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
	}
	
	free(line);
	close(fd);
}
