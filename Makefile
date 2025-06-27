NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRCS =	main.c \
		parsing/tokenizer.c \
		parsing/tokenizer_helper.c \
		parsing/tokens_nodes.c \
		parsing/utils.c \
		parsing/parser.c \
		parsing/parser_helper.c \
		parsing/redirections_nodes.c \
		parsing/cmds_nodes.c \
		EXECUTING/executor.c \
		EXECUTING/path_utils.c \
		EXECUTING/exec_utils.c \
		EXECUTING/built_in_dispatcher.c \
		EXECUTING/builtins/built_in_utils.c \
		EXECUTING/builtins/built_in_cd.c \
		EXECUTING/builtins/built_in_echo.c \
		EXECUTING/builtins/built_in_env.c \
		EXECUTING/builtins/built_in_exit.c \
		EXECUTING/builtins/built_in_export.c \
		EXECUTING/builtins/built_in_pwd.c \
		EXECUTING/builtins/built_in_unset.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
