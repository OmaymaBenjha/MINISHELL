#include "parsing.h"

char    *ft_strdup(char *value)
{
    char *result;
    int i;
    int len;

    len = ft_strlen(value);
    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (value[i] != '\0')
    {
        result[i] = value[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}


static char *strip_quotes(const char *str)
{
    int i = 0, j = 0;
    char *cleaned = malloc(ft_strlen(str) + 1);
    if (!cleaned)
        return (NULL);
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '"')
        {
            cleaned[j++] = str[i];
        }
        i++;
    }
    cleaned[j] = '\0';
    return (cleaned);
}

static void clean_quotes_in_args(t_command *cmd)
{
    int i = 0;
    char *stripped;

    while (cmd->args && cmd->args[i])
    {
        stripped = strip_quotes(cmd->args[i]);
        if (stripped)
        {
            free(cmd->args[i]);
            cmd->args[i] = stripped;
        }
        i++;
    }
}

void remove_quotes_from_all_args(t_command *cmd_list)
{
    while (cmd_list)
    {
        clean_quotes_in_args(cmd_list);
        cmd_list = cmd_list->next_piped_command;
    }
}


void handle_heredocs(t_command *cmd_list)
{
    t_command *cmd = cmd_list;
    t_redir *redir;
    int pipefd[2];
    char *line;

    while (cmd)
    {
        redir = cmd->redirections;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                if (pipe(pipefd) == -1)
                {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }

                while (1)
                {
                    line = readline("> ");
                    if (!line)
                        break;

                    if (strcmp(line, redir->delimiter_or_filename) == 0)
                    {
                        free(line);
                        break;
                    }

                    write(pipefd[1], line, strlen(line));
                    write(pipefd[1], "\n", 1);
                    free(line);
                }

                close(pipefd[1]); 
                redir->fd = pipefd[0]; 
            }
            redir = redir->next;
        }
        cmd = cmd->next_piped_command;
    }
}
