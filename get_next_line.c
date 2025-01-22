#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#define BUFFER_SIZE 5;

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	char		*line;
	int			i;
	int			j;
	ssize_t		nl;

	line = (char *)malloc(get_len(fd, buf) + 1);
	if (!line)
		return ((void *)0);
	nl = read(fd, buf, sizeof(buf));
	if (nl <= 0)
		return ((void *)0);
	j = 0;
	while (nl > 0)
	{
		i = 0;
		while (buf[i] != '\n' && buf[i] != '\0')
		{
			line[j++] = buf[i++];
		}
		nl = read(fd, buf, sizeof(buf));
	}
	line[10] = '\0';
	return (line);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY | O_CREAT);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
	}
	free(line);
	close(fd);
}
