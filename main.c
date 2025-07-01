#include "./PARSING/parsing.h"
#include "./EXECUTING/executing.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input_line;
	t_token		*tokens;
	t_command	*commands;

	(void)argc;
	(void)argv;
	while (1)
	{
		input_line = readline("minishell> ");
		if (!input_line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (input_line[0] != '\0')
		{
			add_history(input_line);
			tokens = tokenize(input_line);
			if (tokens)
			{
				commands = parse(tokens);
				if (!commands)
				{
					free_tokens(tokens);
                    free(input_line);
                    continue;
				}
				executor(commands, envp);
				handle_heredocs(commands);
				free_tokens(tokens);
			}
		}
		free(input_line);
		input_line = NULL;
	}
	return (0);
}
