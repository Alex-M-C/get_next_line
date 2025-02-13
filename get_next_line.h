/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:53:06 by aleconst          #+#    #+#             */
/*   Updated: 2025/01/23 15:53:07 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);

char	*ft_strchr(const char *s, int c);

void	*ft_memmove(void *dest, const void *src, size_t n);

char	*ft_substr(char const *s, unsigned int start, size_t len);
