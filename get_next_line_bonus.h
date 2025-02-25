
#include <stddef.h>

typedef struct s_file
{
	int				fd;
	char			buf[BUFFER_SIZE];
	struct s_file	*next;
}	t_file;

char	*get_next_line(int fd);

size_t	ft_strlen(const char *str);

char	*ft_strchr(const char *s, int c);

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strdup(const char *s);
