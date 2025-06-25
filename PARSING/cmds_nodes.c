#include "parsing.h"

t_command *new_cmd_node(char **args, t_redir *redir)
{
    t_command *cmd;

    if (!args)
        return (NULL);
    cmd = (t_command *)malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = args;
    if (!cmd->args)
        return (NULL);
    cmd->redirections = redir;
    cmd->next_piped_command = NULL;
    return (cmd);
}
void    add_cmd_node(t_command **cmd_head, t_command *cmd_node)
{
    t_command *current;

    if (!cmd_head || !cmd_node)
        return;
    if (*cmd_head == NULL)
        *cmd_head = cmd_node;
    else
    {
        current = *cmd_head;
        while (current->next_piped_command)
            current = current->next_piped_command;
        current->next_piped_command = cmd_node;
    }
}