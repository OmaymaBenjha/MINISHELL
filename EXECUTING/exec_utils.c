#include "executing.h"

size_t	ft_strlen_e(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strncmp_e(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}

char	*ft_strjoin_e(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_strlen_e(s1) + ft_strlen_e(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

char	*ft_strchr_e(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup_e(char *value)
{
	char	*result;
	int		i;
	int		len;

	len = ft_strlen_e(value);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		result[i] = value[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
