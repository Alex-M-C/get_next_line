#include <stddef.h>
#include <stdlib.h>
#include "get_next_line.h"

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
