#include "../executing.h"

void	built_in_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
