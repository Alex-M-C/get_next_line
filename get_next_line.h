/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <aleconst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:35:43 by aleconst          #+#    #+#             */
/*   Updated: 2025/03/03 13:22:22 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE > __INT32_MAX__
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);

char	*ft_strchr(const char *s, int c);

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strdup(const char *s);

#endif