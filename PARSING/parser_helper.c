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

static size_t count_stripped_len(const char *str)
{
    size_t i = 0;
    size_t len = 0;
    bool in_squote = false;
    bool in_dquote = false;

    while (str[i])
    {
        if (str[i] == '\'' && !in_dquote)
        {
            in_squote = !in_squote;
            i++;
            continue;
        }
        else if (str[i] == '"' && !in_squote)
        {
            in_dquote = !in_dquote;
            i++;
            continue;
        }
        len++;
        i++;
    }
    return len;
}

static char *strip_quotes(const char *str)
{
    size_t i = 0, j = 0;
    size_t new_len = count_stripped_len(str);
    char *cleaned = malloc(new_len + 1);
    bool in_squote = false;
    bool in_dquote = false;

    if (!cleaned)
        return NULL;

    while (str[i])
    {
        if (str[i] == '\'' && !in_dquote)
        {
            in_squote = !in_squote;
            i++;
            continue;
        }
        else if (str[i] == '"' && !in_squote)
        {
            in_dquote = !in_dquote;
            i++;
            continue;
        }
        cleaned[j++] = str[i++];
    }
    cleaned[j] = '\0';
    return cleaned;
}


static void clean_quotes_in_args(t_command *cmd)
{
    int i;
    char *stripped;

    i = 0;
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


static void sigint_heredoc_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(1);
}

void handle_heredocs(t_command *cmd_list)
{
    t_command   *cmd = cmd_list;
    t_redir     *redir;

    while (cmd)
    {
        redir = cmd->redirections;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                int pipefd[2];
                if (pipe(pipefd) == -1)
                {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }

                pid_t pid = fork();
                if (pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }

                if (pid == 0) 
                {
                    
                    signal(SIGINT, sigint_heredoc_handler);
                    signal(SIGQUIT, SIG_IGN);
                    close(pipefd[0]);

                    char *line;
                    while (1)
                    {
                        line = readline("> ");
                        if (!line || ft_strncmp(line, redir->delimiter_or_filename, ft_strlen(redir->delimiter_or_filename)) == 0)
                            break;
                        write(pipefd[1], line, ft_strlen(line));
                        write(pipefd[1], "\n", 1);
                        free(line);
                    }
                    free(line);
                    close(pipefd[1]);
                    exit(0);
                }
                else 
                {
                    int status;

                    signal(SIGINT, SIG_IGN);  
                    waitpid(pid, &status, 0);
                    signal(SIGINT, SIG_DFL);  

                    close(pipefd[1]); 

                    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
                    {
                        close(pipefd[0]);
                        redir->fd = -1;
                        printf("\n[heredoc canceled]\n");
                        return; 
                    }

                    redir->fd = pipefd[0]; 
                }
            }
            redir = redir->next;
        }
        cmd = cmd->next_piped_command;
    }
}