#include "executing.h"

int	is_built_in(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp_e(cmd_name, "echo") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "cd") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "pwd") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "unset") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "env") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

int	is_parent_built_in(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp_e(cmd_name, "cd") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "unset") == 0)
		return (1);
	if (ft_strcmp_e(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

void	execute_built_in(t_command *cmd, char **envp)
{
	char	*cmd_name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	cmd_name = cmd->args[0];
	if (ft_strcmp_e(cmd_name, "echo") == 0)
		built_in_echo(cmd);
	else if (ft_strcmp_e(cmd_name, "cd") == 0)
		built_in_cd(cmd, envp);
	else if (ft_strcmp_e(cmd_name, "pwd") == 0)
		built_in_pwd();
	else if (ft_strcmp_e(cmd_name, "export") == 0)
		built_in_export(cmd, envp);
	else if (ft_strcmp_e(cmd_name, "unset") == 0)
		built_in_unset(cmd);
	else if (ft_strcmp_e(cmd_name, "env") == 0)
		built_in_env(envp);
	else if (ft_strcmp_e(cmd_name, "exit") == 0)
		built_in_exit(cmd);
}
