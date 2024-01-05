NAME = minishell
SRCS = tokenize.c microshell.c find_synerr.c process_dollar.c process_token.c process_delimited.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./Libft/libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
SANITIZE = -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(SANITIZE) -o $(NAME) $(OBJS) -L./Libft -lft -lreadline

$(LIBFT):
	$(MAKE) -C ./Libft

%.o: %.c
	$(CC) -c $(SANITIZE) $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C ./Libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./Libft

re: fclean all

.PHONY: all clean fclean re
