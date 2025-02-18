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

#include <stdio.h>
#define BUFFER_SIZE 5

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static char	*ft_strdup(const char *s);

/*
@returns A pointer to the first occurrence of the character C in the string S
or NULL if any occurrence is found.
*/
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return (ft_strdup((char *)s));
		s++;
	}
	if (*s == (unsigned char)c)
		return (ft_strdup((char *)s));
	return ((void *)0);
}

/*
Calculates the length of the string pointed to by STR, 
excluding the terminating NULL byte ('\0').
*/
size_t	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

/*
Copies N bytes from memory area SRC to memory area DEST.
@attention The memory areas may overlap.
@returns A pointer to DEST.
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				count;
	unsigned char		*dest_byte;
	const unsigned char	*src_byte;

	if (!dest && !src)
		return ((void *)0);
	dest_byte = (unsigned char *)dest;
	src_byte = (const unsigned char *)src;
	count = -1;
	if (dest_byte > src_byte)
	{
		while (n--)
		{
			dest_byte[n] = src_byte[n];
		}
	}
	else
	{
		while (++count < n)
		{
			dest_byte[count] = src_byte[count];
		}
	}
	return (dest_byte);
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

/*
Creates a duplicate of S usign malloc(3) to allocate its memory.
@attention The created string can be freed with free(3).
@returns A pointer to the new string.
*/
static char	*ft_strdup(const char *s)
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


static char	*process_buf(char *buf, int buf_size, int fd);
static char	*add_buf(char *buf, int clear);

static char	*process_buf(char *buf, int buf_size, int fd)
{
	char	*line;
	char	*temp;

	line = ft_strchr(buf, '\n');
	if (!line)
	{
		line = add_buf(buf, 1);
		if (read(fd, buf, buf_size) <= 0)
			return (NULL);
		return (process_buf(buf, buf_size, fd));
	}
	else
	{
		temp = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(line) + 1);
		if (!temp)
			return (NULL);
		ft_memmove(buf, line + 1, ft_strlen(line) + ft_strlen(temp));
		line = add_buf(temp, 1);
		free(temp);
	}
	return (line);
}

static char	*add_buf(char *buf, int clear)
{
	static char	*cpy_line = NULL;
	char		*temp;
	int			i;

	i = 0;
	//temp = NULL;
	if (clear == 0)
		return (free(cpy_line), (void *)0);
	if (cpy_line)
	{
		temp = cpy_line;
		i += ft_strlen(cpy_line);
	}
	cpy_line = (char *)malloc((i + ft_strlen(buf) + 1) * sizeof(char));
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
	return (add_buf(buf, 0), line);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY | O_CREAT);
/* 	line = get_next_line(fd);

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
