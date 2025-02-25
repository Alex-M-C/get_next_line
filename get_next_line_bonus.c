
#include <stddef.h>
#include <stdlib.h>
#define BUFFER_SIZE 42

char	*ft_strdup(const char *s);
/*
Calculates the length of the string pointed to by STR, 
excluding the terminating NULL byte ('\0').
*/
size_t	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (str && str[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

/*
@returns A pointer to the first occurrence of the character C in the string S
or NULL if any occurrence is found.
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return ((void *)0);
}

/*
Allocates memory with malloc(3) for creating a string
resulting in the concatenation of S1 and S2, ensuring 
that the new string will be NULL-terminated ('\0').
@returns The created string or NULL if malloc(3) fails.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		count;
	int		s1_len;

	s1_len = ft_strlen(s1);
	newstr = (char *)malloc((s1_len + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstr)
		return ((void *)0);
	count = 0;
	while (count < s1_len)
	{
		newstr[count] = (char)s1[count];
		count++;
	}
	count = 0;
	while (s2[count] != '\0')
	{
		newstr[count + s1_len] = (char)s2[count];
		count++;
	}
	newstr[count + s1_len] = '\0';
	return (newstr);
}

/*
Copies the string pointed to by SRC, including the terminating 
NULL byte ('\0'), to DEST. The copy is truncated if DEST length is
lower than SRC length, this can be checked by seeing the return value. 
@attention The strings may not overlap.
@returns The length of SRC
*/
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	if (!dest || !src)
		return (ft_strlen(src));
	count = 0;
	if (size > 0)
	{
		while (count < size - 1 && src[count] != '\0')
		{
			dest[count] = src[count];
			count++;
		}
		dest[count] = '\0';
	}
	return (ft_strlen(src));
}

/* 
Allocates memory with malloc(3) for crating a substring from the
string S starting at START and with a length of LEN + 1 including 
the NULL byte ('\0') at the end.
@returns The created substring or NULL if malloc(3) fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			count;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return ((void *)0);
	count = 0;
	while (count < len && s[count] != '\0')
	{
		substr[count] = (char)s[count + start];
		count++;
	}
	substr[count] = '\0';
	return (substr);
}

typedef struct s_file
{
	int				fd;
	char			buf[BUFFER_SIZE];
	struct s_file	*next;
}	t_file;

#include <unistd.h>
#include <stdlib.h>

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

	line_end = ft_strchr(buf, '\n');
	if (!line_end)
	{
		add_to_line(line, buf);
		if (!*line)
			return (3);
		i = 0;
		while (i < BUFFER_SIZE)
			buf[i++] = '\0';
		return (0);
	}
	buf_keep = ft_strdup(line_end);
	ft_strlcpy(buf_keep, line_end + 1, ft_strlen(line_end + 1) + 1);
	line_end = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(line_end) + 1);
	add_to_line(line, line_end);
	if (!line_end || !buf_keep || !*line)
		return (3);
	ft_strlcpy(buf, buf_keep, BUFFER_SIZE);
	return (buf[BUFFER_SIZE - 1] = '\0', free(line_end), free(buf_keep), 1);
}

char	*process_tlist(int fd, char *buf)
{
	char		*line;
	ssize_t		nl;
	int			line_ready;

	line = ft_strdup("");
	nl = 1;
	line_ready = 0;
	while (line_ready == 0)
	{
		if (buf[0] == '\0')
			nl = read(fd, buf, BUFFER_SIZE);
		if (nl <= 0 && ft_strlen(line) == 0)
			return (free(line), NULL);
		else if (nl <= 0 && line)
			return (line);
		line_ready = process_line(buf, &line);
		if (line_ready == 3)
			return (free(line), NULL);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_file	*file;
	t_file			*fnode;

	if (file)
		fnode = file;
	while (fnode)
	{
		if (fnode->fd == fd)
			return (process_tlist(fnode->fd, fnode->buf));
		fnode = fnode->next;
	}
	fnode = malloc(sizeof(t_file));
	if (!fnode)
		return (NULL);
	fnode->fd = fd;
	return (process_tlist(fnode->fd, fnode->buf));
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	int		fd2;
	char	*line;

	fd = open("test.txt", O_RDONLY | O_CREAT, 777);
	fd2 = open("quijote_test.txt", O_RDONLY | O_CREAT, 777);
	line = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("File 1: %s", line);
		line = get_next_line(fd2);
		if (!line)
			break ;
		printf("File 2: %s", line);
	}
	free(line);
	close(fd);
}
