#include "parsing.h"

t_redir *new_redir(t_token_type type, t_token *next_token)
{
    t_redir *redir;

    if (next_token == NULL  || next_token->type != TOKEN_WORD)
        return (NULL);
    redir = (t_redir *)malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->next = NULL;
    redir->delimiter_or_filename = ft_strdup(next_token->value);
    if (!redir->delimiter_or_filename)
        return (free(redir), NULL);
    if (type == TOKEN_REDIR_IN)
        redir->type = REDIR_INPUT;
    else if (type == TOKEN_REDIR_OUT)
        redir->type = REDIR_OUTPUT_TRUNC;
    else if (type == TOKEN_REDIR_APPEND)
        redir->type = REDIR_OUTPUT_APPEND;
    else if (type == TOKEN_REDIR_HEREDOC)
        redir->type = REDIR_HEREDOC;
    else
        return (free(redir), NULL);
    return (redir);
}

void    add_redir_node(t_redir **redir_head, t_redir *new_node)
{
    t_redir *current;

    if (!redir_head || !new_node)
        return;
    if (*redir_head == NULL)
        *redir_head = new_node;
    else
    {
        current = *redir_head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}