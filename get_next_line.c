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

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	char		*line;
	ssize_t		nl;

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
	if (line)
	{
		printf("%s\n", line);
	}

	/*
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
	}
	*/
	free(line);
	close(fd);
}
