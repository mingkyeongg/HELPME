NAME = minishell
SRCS =	tokenize.c \
		microshell.c \
		find_synerr.c \
		process_dollar.c \
		process_token.c \
		process_delimited.c \
		./builtin/make_envp.c \
		./builtin/make_args.c \
		./builtin/ft_builtin.c \
		./builtin/ft_cd.c \
		./builtin/ft_echo.c \
		./builtin/ft_env.c \
		./builtin/ft_export.c \
		./builtin/ft_pwd.c \
		./builtin/ft_unset.c \
		./monitoring/print_envp_args.c
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
