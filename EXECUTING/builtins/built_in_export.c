#include "../executing.h"

void	built_in_export(t_command *cmd, char **envp)
{
	int	i;

	i = 0;
	if (cmd->args[1] != NULL)
	{
		ft_putstr_fd("minishell: export: no options supported\n", 2);
		return ;
	}
	while (envp && envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
