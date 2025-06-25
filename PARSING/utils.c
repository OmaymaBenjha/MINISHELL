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