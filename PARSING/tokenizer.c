#include "parsing.h"
#include <unistd.h>
#include <stdio.h>

static t_token *try_tokenize_operator(const char *input, int *pos_ptr, int input_len)
{
    t_token *new_node;
    int     current_pos;

    new_node = NULL;
    current_pos = *pos_ptr;
    if (input[current_pos] == '<' && (current_pos + 1 < input_len && input[current_pos + 1] == '<'))
    {
        new_node = new_token(TOKEN_REDIR_HEREDOC, &input[current_pos], 2);
        *pos_ptr = current_pos + 2;
    }
    else if (input[current_pos] == '>' && (current_pos + 1 < input_len && input[current_pos + 1] == '>'))
    {
        new_node = new_token(TOKEN_REDIR_APPEND, &input[current_pos], 2);
        *pos_ptr = current_pos + 2;
    }
    else if (input[current_pos] == '|')
    {
        new_node = new_token(TOKEN_PIPE, &input[current_pos], 1);
        *pos_ptr = current_pos + 1;
    }
    else if (input[current_pos] == '<')
    {
        new_node = new_token(TOKEN_REDIR_IN, &input[current_pos], 1);
        *pos_ptr = current_pos + 1;
    }
    else if (input[current_pos] == '>')
    {
        new_node = new_token(TOKEN_REDIR_OUT, &input[current_pos], 1);
        *pos_ptr = current_pos + 1;
    }
    return (new_node);
}




static t_token *get_next_token(const char *input, int *pos_ptr, int input_len, t_token **tokens_so_far_for_cleanup)
{
    t_token *new_node;

    if (skip_whitespace(input, pos_ptr, input_len))
        return (NULL);
    new_node = try_tokenize_operator(input, pos_ptr, input_len); 
    if (new_node == NULL && *pos_ptr < input_len && input[*pos_ptr] != '|' && input[*pos_ptr] != '<' && input[*pos_ptr] != '>')
        new_node = tokenize_word_or_handle_error(input, pos_ptr, input_len, tokens_so_far_for_cleanup);
    if (new_node == NULL && *pos_ptr < input_len && (*tokens_so_far_for_cleanup != NULL || !skip_whitespace(input, pos_ptr, input_len)))
    {
        if (*tokens_so_far_for_cleanup != NULL || (input[*pos_ptr-1] && (input[*pos_ptr-1] == '|' || input[*pos_ptr-1] == '<' || input[*pos_ptr-1] == '>')))
        {
             perror("minishell: get_next_token (new_token allocation failed)");
             free_tokens(*tokens_so_far_for_cleanup);
             *tokens_so_far_for_cleanup = NULL;
             *pos_ptr = input_len;
        }
        return (NULL);
    }
    return (new_node);
}

t_token *tokenize(const char *input)
{
    t_token *tokens_head;
    t_token *new_node;
    int     current_pos;
    int     input_len;

    if (!input)
        return (NULL);
    tokens_head = NULL;
    current_pos = 0;
    input_len = ft_strlen(input);
    while (current_pos < input_len)
    {
        new_node = get_next_token(input, &current_pos, input_len, &tokens_head);
        if (new_node == NULL)
        {
            if (tokens_head != NULL && current_pos < input_len)
                return (NULL);
            break;
        }
        add_token(&tokens_head, new_node);
    }
    return (tokens_head);
}