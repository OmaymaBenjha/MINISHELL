#include "parsing.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(const char *s, int fd)
{
    if (s)
        write(fd, s, ft_strlen(s));
}

bool skip_whitespace(const char *input, int *pos_ptr, int input_len)
{
    while (*pos_ptr < input_len && (input[*pos_ptr] == '\t' || input[*pos_ptr] == ' '))
        (*pos_ptr)++;
    return (*pos_ptr >= input_len);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
