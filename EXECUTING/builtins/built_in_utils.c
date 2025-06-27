#include "../executing.h"

int	ft_strcmp_e(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*get_env_var_value(char *var_name, char **envp)
{
	int		i;
	int		len;
	char	*equals_sign;

	if (!var_name || !envp)
		return (NULL);
	len = ft_strlen_e(var_name);
	i = 0;
	while (envp[i])
	{
		equals_sign = ft_strchr_e(envp[i], '=');
		if (equals_sign)
		{
			if (ft_strncmp_e(envp[i], var_name, len) == 0
				&& (equals_sign - envp[i]) == len)
			{
				return (equals_sign + 1);
			}
		}
		i++;
	}
	return (NULL);
}
