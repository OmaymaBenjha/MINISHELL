#include "parsing.h" 
#include <stdio.h> 

t_token *new_token(t_token_type type, const char *value_start, int len)
{
    t_token *token;
    int     i;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->next = NULL;
    token->value = NULL;
    i = 0;
    if (value_start && len > 0)
    {
        token->value = (char *)malloc(sizeof(char) * (len + 1));
        if (!token->value)
            return (free(token), NULL);
        while (i < len)
        {
            token->value[i] = value_start[i];
            i++;
        }
        token->value[len] = '\0';
    }
    return (token);
}
void    add_token(t_token **list_head, t_token *new_node)
{
    t_token *current;

    if (!list_head || !new_node)
        return;
    if (*list_head == NULL)
        *list_head = new_node;
    else
    {
        current = *list_head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void    free_token(t_token *token_node)
{
    if (!token_node)
        return;
    free(token_node->value);
    token_node->value = NULL;
    free(token_node);
}

void    free_tokens(t_token *list_head)
{
    t_token *current;
    t_token *next_node;

    current = list_head;
    while (current != NULL)
    {
        next_node = current->next;
        free_token(current);
        current = next_node;
    }
}