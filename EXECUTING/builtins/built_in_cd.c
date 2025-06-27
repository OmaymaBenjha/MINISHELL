#include "../executing.h"

void	built_in_cd(t_command *cmd, char **envp)
{
	char	*path;

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	path = cmd->args[1];
	if (!path)
	{
		path = get_env_var_value("HOME", envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
	}
}
