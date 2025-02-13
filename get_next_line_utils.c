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

#include <stdlib.h>

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
