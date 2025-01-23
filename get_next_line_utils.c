/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:51:15 by aleconst          #+#    #+#             */
/*   Updated: 2025/01/23 15:51:17 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static size_t	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

static size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	counter;
	size_t	dest_end;

	counter = 0;
	dest_end = ft_strlen(dest);
	if (size <= dest_end)
	{
		return (size + ft_strlen(src));
	}
	while (src[counter] != '\n' && src[counter] != '\0'
		&& (dest_end + counter) < size - 1)
	{
		dest[dest_end + counter] = src[counter];
		counter++;
	}
	dest[dest_end + counter] = '\0';
	return (dest_end + ft_strlen(src));
}

char	*add_buf(char *buf)
{
	static char	*cpy_line = NULL;
	char		*temp;
	int			i;

	i = 0;
	temp = NULL;
	if (cpy_line)
	{
		temp = cpy_line;
		i += ft_strlen(cpy_line);
	}
	cpy_line = (char *)malloc((i + ft_strlen(buf) + 1) * sizeof(char));
	if (!cpy_line)
		return ((void *)0);
	if (temp)
		ft_strlcat(cpy_line, temp, ft_strlen(temp));
	if (buf)
		ft_strlcat(cpy_line, buf, ft_strlen(buf));
	return (cpy_line);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*line;
	char	buf[5];

	buf[0] = '1';
	buf[1] = '2';
	buf[2] = '3';
	buf[3] = '4';
	buf[4] = '5';
	line = add_buf(buf);
	buf[0] = '6';
	buf[1] = '7';
	buf[2] = '8';
	buf[3] = '9';
	buf[4] = '0';
	line = add_buf(buf);
	if (line)
		printf("%s\n", line);
	else
		printf("%s\n", "null");
	free(line);
	return (0);
}
*/