#include "../executing.h"

void	built_in_unset(t_command *cmd)
{
	if (cmd->args[1] != NULL)
	{
		ft_putstr_fd("minishell: unset: no options supported\n", 2);
	}
}
