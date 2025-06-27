#include "parsing.h"

static int get_piped_cmds_count(t_token *tokens)
{
    int cmd_count = 1;

    while (tokens)
    {
        if (tokens->type == TOKEN_PIPE)
            cmd_count++;
        tokens = tokens->next;
    }
    return (cmd_count);
}

static int get_args_per_cmd(t_token *tokens)
{
    int args_count = 0;

    while (tokens && tokens->type != TOKEN_PIPE)
    {
        if (tokens->type == TOKEN_WORD)
            args_count++;
        tokens = tokens->next;
    }
    return (args_count);
}

t_command *parse(t_token *tokens)
{
    int         cmds_count;
    int         i;
    int         arg_count;
    int         arg_index;
    char        **args;
    t_redir     *redir;
    t_redir     *redir_head;
    t_command   *cmd_node;
    t_command   *cmd_head;

    if (!tokens)
        return (NULL);
    cmds_count = get_piped_cmds_count(tokens);
    cmd_head = NULL;
    i = 0;
    while (i < cmds_count)
    {
        arg_index = 0;
        redir = NULL;
        redir_head = NULL;
        arg_count = get_args_per_cmd(tokens);
        args = malloc(sizeof(char *) * (arg_count + 1));
        if (!args)
            return (NULL);
        while (tokens && tokens->type != TOKEN_PIPE)
        {
            if (tokens->type == TOKEN_ERROR)
                return ( NULL);
            if (tokens->type == TOKEN_WORD)
            {
                args[arg_index] = ft_strdup(tokens->value);
                if (!args[arg_index])
                    return (NULL);
                arg_index++;
            }
            else
            {
                redir = new_redir(tokens->type, tokens->next);
                if (!redir)
                    return ( NULL);
                add_redir_node(&redir_head, redir);
                tokens = tokens->next; 
            }
            tokens = tokens->next;
        }
        if (tokens && tokens->type == TOKEN_PIPE && tokens->next == NULL)
        {
            printf("[ERROR] Pipe without following command\n");
            return (NULL);
        }
        if (tokens && tokens->type == TOKEN_REDIR_HEREDOC && tokens->next == NULL)
        {
            printf("syntax error near unexpected token `newline'\n");
            return (NULL);
        }

        args[arg_index] = NULL;
        cmd_node = new_cmd_node(args, redir_head);
        if (!cmd_node)
            return (NULL);
        add_cmd_node(&cmd_head, cmd_node);
        if (tokens)
            tokens = tokens->next; 
        i++;
    }
    remove_quotes_from_all_args(cmd_head);
    return (cmd_head);
}
