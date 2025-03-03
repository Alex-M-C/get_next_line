/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <aleconst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:35:22 by aleconst          #+#    #+#             */
/*   Updated: 2025/02/26 17:26:37 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

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
	while (i < BUFFER_SIZE)
		buf[i++] = '\0';
	if (!line_end || !buf_keep || !*line)
		return (free(line_end), free(buf_keep), 3);
	ft_strlcpy(buf, buf_keep, BUFFER_SIZE);
	return (free(line_end), free(buf_keep), 1);
}

static int	initialize_fd_buf(int fd, char **fd_buf, char **line)
{
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (*line = NULL, 3);
	if (!fd_buf[fd])
	{
		fd_buf[fd] = (char *)malloc(BUFFER_SIZE + 1);
		if (!fd_buf[fd])
			return (*line = NULL, 3);
		fd_buf[fd][0] = '\0';
	}
	*line = ft_strdup("");
	if (!*line)
		return (*line = NULL, 3);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*fd_buf[1024];
	char		*line;
	ssize_t		nl;
	int			line_ready;

	nl = 1;
	line_ready = initialize_fd_buf(fd, fd_buf, &line);
	while (line_ready == 0)
	{
		if (fd_buf[fd][0] == '\0')
		{
			nl = read(fd, fd_buf[fd], BUFFER_SIZE);
			if (nl > 0)
				fd_buf[fd][nl] = '\0';
		}
		if (nl == -1 || (nl == 0 && ft_strlen(line) == 0))
			return (free(line), free(fd_buf[fd]), fd_buf[fd] = NULL, NULL);
		else if (nl == 0)
			return (line);
		line_ready = process_line(fd_buf[fd], &line);
		if (line_ready == 3)
			return (free(line), free(fd_buf[fd]), fd_buf[fd] = NULL, NULL);
	}
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>
typedef struct s_list
{
	char            *line;
	struct s_list   *next;
}   t_list;

int main(void)
{
	int fd1, fd2;
	char *line1, *line2;
	t_list *lines1 = NULL, *lines2 = NULL, 
		*temp, *new_node, *last1 = NULL, *last2 = NULL;

	fd1 = open("quijote_test.txt", O_RDONLY);
	fd2 = open("quijote.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		perror("Error al abrir los archivos");
		return (1);
	}

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);

		if (!line1 && !line2)
			break;

		if (line1)
		{
			new_node = (t_list *)malloc(sizeof(t_list));
			if (!new_node)
				return (1);
			new_node->line = line1;
			new_node->next = NULL;
			if (!lines1)
				lines1 = new_node;
			else
				last1->next = new_node;
			last1 = new_node;
		}
		if (line2)
		{
			new_node = (t_list *)malloc(sizeof(t_list));
			if (!new_node)
				return (1);
			new_node->line = line2;
			new_node->next = NULL;
			if (!lines2)
				lines2 = new_node;
			else
				last2->next = new_node;
			last2 = new_node;
		}
	}

	close(fd1);
	close(fd2);

	printf("\n--- Contenido de file1.txt ---\n");
	temp = lines1;
	while (temp)
	{
		printf("%s", temp->line);
		free(temp->line);
		new_node = temp;
		temp = temp->next;
		free(new_node);
	}

	printf("\n--- Contenido de file2.txt ---\n");
	temp = lines2;
	while (temp)
	{
		printf("%s", temp->line);
		free(temp->line);
		new_node = temp;
		temp = temp->next;
		free(new_node);
	}

	return (0);
} */
