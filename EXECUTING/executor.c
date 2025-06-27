#include "executing.h"

static void	child_actions(t_command *cmd, char **envp)
{
	char	*path;

	if (is_built_in(cmd->args[0]))
	{
		execute_built_in(cmd, envp);
		exit(0);
	}
	path = get_cmd_path(cmd->args[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->args, envp);
	perror("minishell: execve");
	free(path);
	exit(1);
}

static void	handle_one_cmd(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		child_actions(cmd, envp);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void	executor(t_command *cmd, char **envp)
{
	if (!cmd)
		return ;
	if (cmd->next_piped_command == NULL && is_parent_built_in(cmd->args[0]))
	{
		execute_built_in(cmd, envp);
	}
	else if (cmd->next_piped_command == NULL)
	{
		handle_one_cmd(cmd, envp);
	}
}
