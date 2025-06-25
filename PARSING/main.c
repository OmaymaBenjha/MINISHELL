#include "parsing.h" 
#include <stdio.h>   




void ff()
{
    system("leaks minishell");
}
int main(int argc, char **argv, char **envp) 
{ 
    char *input_line;
    t_token *tokens;
    t_command *parsed_commands; 
    (void)argc;
    (void)argv;
    (void)envp;
    atexit(ff);
    while (1) {
        input_line = readline("minishell> ");

        if (input_line == NULL) { // Ctrl-D
            printf("exit\n"); 
            break;
        }

        if (input_line[0] != '\0') { 
            add_history(input_line);

            // printf("Input: [%s]\n", input_line);
            tokens = tokenize(input_line);


            
            if (tokens) { 
                
                parsed_commands = parse(tokens); 
              
                handle_heredocs(parsed_commands); 
           
            //     // if (parsed_commands) {
            //     //     // execute_pipeline(parsed_commands, envp);
            //     //     // free_command_pipeline(parsed_commands);
            //     // }
            // }
            if (tokens != NULL) { 
                free_tokens(tokens);
                tokens = NULL;
            }
        }

        free(input_line); 
        input_line = NULL;
    }
    }
    return 0;
}