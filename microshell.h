#ifndef MICROSHELL_H
#define MICROSHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

typedef struct s_comm
{
	char			*token;
	int				length;
	int				type;
	int				pipes[2];
	struct s_comm	*prev;
	struct s_comm	*next;
} t_comm;

#define STR 0
#define PIPE 1
#define DLESS 2 // <<
#define LESS 3 // <
#define DGREAT 4 // >>
#define GREAT 5 // >

#define SYNTAX_ERR 258

/* tokenize */
void 	split_line(char *line, t_comm **cmd);
char 	*mk_strdup(int start, int end, char *line);
void 	process_env_var(char **token);
void 	init_list(t_comm **cmd, char *token, int type);

int 	process_dquo(char *line, int start, char **temp, t_comm **cmd);

int 	is_space(char a);
int 	is_dquotes(char a);
int 	is_squotes(char a);
int 	is_del(char *line);

int 	find_syntax_err(char *buf);

int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

#endif