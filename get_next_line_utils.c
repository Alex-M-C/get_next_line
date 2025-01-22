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

char	*add_buf(char *buf)
{
	static char	*cpy_line;
	char		*temp;
	int			i;
	int			j;

	i = 0;
	j = -1;

	temp = "\0";
	if (cpy_line)
	{
		temp = cpy_line;
		i += ft_strlen(cpy_line);
	}
	cpy_line = (char *)malloc((i + ft_strlen(buf) + 1) * sizeof(char));
	if (!cpy_line)
		return ((void *)0);
	while (temp[++j] != '\0')
		cpy_line[j] = temp[j];
	j = 0;
	while (buf[j] != '\n' && buf[j] != '\0')
		cpy_line[i++] = buf[j++];
	cpy_line[i] = '\0';
	return (cpy_line);
}

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
	{
		printf("%s\n", line);
	}
	else
	{
		printf("%s\n", "null");
	}
	free(line);
	return (0);
}
