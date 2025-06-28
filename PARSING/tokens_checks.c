#include "parsing.h"
int only_redi(t_command *cmds)
{
    t_command *cmd;
    int any_args;
    int is_pipe;

    is_pipe;
    cmd = cmds;
    any_args = 0;

    while (cmd)
    {
        if (cmd->args != NULL)
            any_args = 1;
        cmd = cmd->next_piped_command;
    }

    
}
int checks(t_command *cmd_list)
{
    t_command *cmds;
    int status;

    status = 0;
    
    cmd = cmd_list;

}