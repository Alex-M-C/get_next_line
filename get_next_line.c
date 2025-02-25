/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <aleconst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:35:22 by aleconst          #+#    #+#             */
/*   Updated: 2025/02/25 17:08:52 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

/*
Creates a duplicate of S usign malloc(3) to allocate its memory.
@attention The created string can be freed with free(3).
@returns A pointer to the new string.
*/
char	*ft_strdup(const char *s)
{
	int		count;
	char	*s_dup;

	count = 0;
	s_dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!s_dup)
		return ((void *)0);
	while (s[count] != '\0')
	{
		s_dup[count] = s[count];
		count++;
	}
	s_dup[count] = '\0';
	return (s_dup);
}

static void	add_to_line(char **line, char *to_add)
{
	char	*temp;

	if (!to_add)
		return ;
	temp = ft_strjoin(*line, to_add);
	free(*line);
	*line = temp;
}

static int	process_line(char *buf, char **line)
{
	char	*line_end;
	char	*buf_keep;
	int		i;

	i = 0;
	line_end = ft_strchr(buf, '\n');
	if (!line_end)
	{
		add_to_line(line, buf);
		if (!*line)
			return (3);
		while (i < BUFFER_SIZE)
			buf[i++] = '\0';
		return (0);
	}
	buf_keep = ft_strdup(line_end + 1);
	line_end = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(line_end) + 1);
	add_to_line(line, line_end);
	if (!line_end || !buf_keep || !*line)
		return (free(line_end), free(buf_keep), 3);
	while (i < BUFFER_SIZE)
		buf[i++] = '\0';
	ft_strlcpy(buf, buf_keep, BUFFER_SIZE);
	return (free(line_end), free(buf_keep), 1);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;
	ssize_t		nl;
	int			line_ready;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	nl = 1;
	line_ready = 0;
	while (line_ready == 0)
	{
		if (buf[0] == '\0')
			nl = read(fd, buf, BUFFER_SIZE);
		if (nl <= 0)
			return (free(line), NULL);
		line_ready = process_line(buf, &line);
		if (line_ready == 3)
			return (free(line), NULL);
		if (!line)
			return (NULL);
	}
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("quijote_test.txt", O_RDONLY | O_CREAT, 777);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */
