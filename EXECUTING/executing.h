#ifndef EXECUTING_H
# define EXECUTING_H

# include "../PARSING/parsing.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>

void	executor(t_command *cmd, char **envp);
char	*get_cmd_path(char *cmd, char **envp);

int		is_built_in(char *cmd_name);
int		is_parent_built_in(char *cmd_name);
void	execute_built_in(t_command *cmd, char **envp);
void	built_in_echo(t_command *cmd);
void	built_in_cd(t_command *cmd, char **envp);
void	built_in_pwd(void);
void	built_in_export(t_command *cmd, char **envp);
void	built_in_unset(t_command *cmd);
void	built_in_env(char **envp);
void	built_in_exit(t_command *cmd);

char	*get_env_var_value(char *var_name, char **envp);
int		ft_strcmp_e(char *s1, char *s2);
size_t	ft_strlen_e(const char *s);
int		ft_strncmp_e(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_e(char const *s1, char const *s2);
char	*ft_strchr_e(const char *s, int c);
char	*ft_strdup_e(char *value);

#endif
