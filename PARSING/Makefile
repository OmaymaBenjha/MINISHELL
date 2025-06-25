NAME = minishell 
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline 
RM = rm -f

SRCS = main.c tokenizer.c tokenizer_helper.c tokens_nodes.c utils.c parser.c parser_helper.c redirections_nodes.c cmds_nodes.c
OBJS = $(SRCS:.c=.o)
HEADERS = parsing.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) # <--- PASS $(LDFLAGS) HERE

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re