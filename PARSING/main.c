#include "parsing.h" 
#include <stdio.h>   

int main(int argc, char **argv, char **envp) 
{ 
    char *input_line;
    t_token *tokens;
    t_command *parsed_commands; 
    (void)argc;
    (void)argv;
    (void)envp;
    if (isatty(STDIN_FILENO)) 
    {
       
        while (1) 
        {
            input_line = readline("minishell> ");
            if (input_line == NULL)
            {
                printf("exit\n"); 
                break;
            }
            if (input_line[0] != '\0') 
            { 
                add_history(input_line);
                tokens = tokenize(input_line);
                if (!tokens)
                {
                    free(input_line);
                    continue ;
                }
                parsed_commands = parse(tokens); 
                if (!parsed_commands)
                {
                    free_tokens(tokens);
                    free(input_line);
                    continue;
                }
                handle_heredocs(parsed_commands);
            //     // if (parsed_commands) {
            //     //     // execute_pipeline(parsed_commands, envp);
            //     //     // free_command_pipeline(parsed_commands);
            //     // }
            // }
            }
            // free_tokens(tokens);
            free(input_line); 
            input_line = NULL;
        }
    }
    return 0;
}