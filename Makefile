NAME = minishell
SRCS =	./tokenizing/find_synerr.c \
		microshell.c \
		./tokenizing/pre_processing.c \
		./tokenizing/process_delimited.c \
		./tokenizing/process_dollar.c \
		./tokenizing/process_remove.c \
		./tokenizing/put_on_list.c \
		./tokenizing/search_dollar_env.c \
		./tokenizing/token_utils_two.c \
		./tokenizing/token_utils.c \
		./tokenizing/tokenize.c \
		./tokenizing/utils_quotes.c \
		./tokenizing/work_inside_quotes.c \
		./builtin/make_envp.c \
		./builtin/make_args.c \
		./builtin/ft_builtin.c \
		./builtin/ft_cd.c \
		./builtin/ft_echo.c \
		./builtin/ft_env.c \
		./builtin/ft_export.c \
		./builtin/ft_pwd.c \
		./builtin/ft_unset.c \
		./builtin/ft_exit.c \
		./monitoring/print_envp_args.c \
		./redirection/exe_redirection.c \
		./redirection/ft_redirection.c

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
