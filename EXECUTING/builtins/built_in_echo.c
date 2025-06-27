#include "../executing.h"

static int	check_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

void	built_in_echo(t_command *cmd)
{
	int		i;
	int		newline_flag;

	i = 1;
	newline_flag = 1;
	while (cmd->args[i] && check_n_option(cmd->args[i]))
	{
		newline_flag = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline_flag)
		ft_putstr_fd("\n", 1);
}
