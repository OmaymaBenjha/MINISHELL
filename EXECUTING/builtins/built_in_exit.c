#include "../executing.h"

void	built_in_exit(t_command *cmd)
{
	if (cmd->args[1])
	{
		ft_putstr_fd("minishell: exit: no options supported\n", 2);
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
