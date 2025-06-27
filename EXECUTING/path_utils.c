#include "executing.h"

static char	*try_paths(char *cmd, char *all_paths)
{
	char	*path_part;
	char	*full_path;
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (all_paths && all_paths[i])
	{
		if (all_paths[i] == ':')
		{
			all_paths[i] = '\0';
			path_part = ft_strjoin_e(&all_paths[start], "/");
			full_path = ft_strjoin_e(path_part, cmd);
			free(path_part);
			if (access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			start = i + 1;
		}
		i++;
	}
	path_part = ft_strjoin_e(&all_paths[start], "/");
	full_path = ft_strjoin_e(path_part, cmd);
	free(path_part);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	char	*paths_copy;
	char	*path_found;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr_e(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup_e(cmd));
		return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strncmp_e(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_env = envp[i] + 5;
	paths_copy = ft_strdup_e(path_env);
	if (!paths_copy)
		return (NULL);
	path_found = try_paths(cmd, paths_copy);
	free(paths_copy);
	return (path_found);
}
