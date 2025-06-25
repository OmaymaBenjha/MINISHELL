#ifndef PARSING_H
#define PARSING_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_REDIR_HEREDOC,
    TOKEN_NEWLINE,
    TOKEN_EOF,
    TOKEN_ERROR
    
} t_token_type;

typedef struct  s_token
{
    t_token_type    type;
    char            *value;
    struct  s_token *next;
} t_token;

typedef enum e_redir_type
{
    REDIR_NONE,
    REDIR_INPUT,
    REDIR_OUTPUT_TRUNC,
    REDIR_OUTPUT_APPEND,
    REDIR_HEREDOC
} t_redir_type;

typedef struct s_redir
{
    t_redir_type    type;
    char            *delimiter_or_filename;
    int             fd;    
    struct  s_redir *next;
} t_redir;

typedef struct s_command
{
    char                **args;
    t_redir             *redirections;
    struct  s_command   *next_piped_command;
} t_command;

t_token *tokenize(const char *input);
t_token *tokenize_word_or_handle_error(const char *input, int *pos_ptr, int input_len, t_token **tokens_so_far_for_cleanup);
bool    handle_unclosed_quote_error(t_token **tokens_so_far_for_cleanup, int *pos_ptr, int input_len);
bool    skip_whitespace(const char *input, int *pos_ptr, int input_len);
t_token *scan_and_create_word(const char *input, int *pos_ptr, int input_len, int word_start, t_token **tokens_so_far_for_cleanup);
void    ft_putstr_fd(const char *s, int fd);
size_t  ft_strlen(const char *s);

t_token *new_token(t_token_type type, const char *value_start, int len);
void    add_token(t_token **list_head, t_token *new_node);
void    free_token(t_token *token_node);
void    free_tokens(t_token *list_head);
char    *ft_strdup(char *value);
t_command *parse(t_token *tokens);
t_command *new_cmd_node(char **args, t_redir *redir);
void    add_cmd_node(t_command **cmd_head, t_command *cmd_node);
t_redir *new_redir(t_token_type type, t_token *next_token);
void    add_redir_node(t_redir **redir_head, t_redir *new_node);
void remove_quotes_from_all_args(t_command *cmd_list);
void handle_heredocs(t_command *cmd_list);

#endif