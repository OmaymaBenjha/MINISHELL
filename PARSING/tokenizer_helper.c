#include "parsing.h"

bool handle_unclosed_quote_error(t_token **tokens_so_far_for_cleanup, int *pos_ptr, int input_len)
{
    ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
    free_tokens(*tokens_so_far_for_cleanup);
    *tokens_so_far_for_cleanup = NULL;
    *pos_ptr = input_len;
    return (true);
}

t_token *tokenize_word_or_handle_error(const char *input, int *pos_ptr, int input_len, t_token **tokens_so_far_for_cleanup)
{
    t_token *new_node;
    int     word_start;

    word_start = *pos_ptr;
    new_node = scan_and_create_word(input, pos_ptr, input_len, word_start, tokens_so_far_for_cleanup);
    if (new_node == NULL && *pos_ptr < input_len && *pos_ptr == word_start && !(*tokens_so_far_for_cleanup == NULL && *pos_ptr == input_len))
    {
        ft_putstr_fd("minishell: syntax error near unexpected character '", 2);
        write(2, &input[word_start], 1);
        ft_putstr_fd("'\n", 2);
        free_tokens(*tokens_so_far_for_cleanup);
        *tokens_so_far_for_cleanup = NULL;
        *pos_ptr = input_len;
        return (NULL);
    }
    return (new_node);
}

t_token *scan_and_create_word(const char *input, int *pos_ptr, int input_len, int word_start, t_token **tokens_so_far_for_cleanup)
{
    bool in_squote;
    bool in_dquote;

    in_squote = false;
    in_dquote = false;
    while (*pos_ptr < input_len)
    {
        if (*pos_ptr == word_start && input[*pos_ptr] == '&')
        {
            printf("minishell: syntax error near unexpected token `&'")
        }
        if (input[*pos_ptr] == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (input[*pos_ptr] == '"' && !in_squote)
            in_dquote = !in_dquote;
        else if (!in_squote && !in_dquote &&
                 (input[*pos_ptr] == '\t' || input[*pos_ptr] == ' ' ||
                  input[*pos_ptr] == '|' || input[*pos_ptr] == '<' || input[*pos_ptr] == '>'))
            break;
        (*pos_ptr)++;
    }
    if (in_squote || in_dquote)
    {
         if (handle_unclosed_quote_error(tokens_so_far_for_cleanup, pos_ptr, input_len))
            return (NULL);
    }
       
    if (*pos_ptr > word_start)
        return (new_token(TOKEN_WORD, &input[word_start], *pos_ptr - word_start));
    return (NULL);
}