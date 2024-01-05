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

typedef struct s_envp
{
	int		state;
	char	*key;
	char	*value;
	t_envp	*next;
} t_envp;


#define STR 0
#define PIPE 1
#define DLESS 2 // <<
#define LESS 3 // <
#define DGREAT 4 // >>
#define GREAT 5 // >

#define HAS_EQUAL 10 // envp_state
#define NO_EQUAL 11

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

char	**put_args(char **args, char *token, int cnt);
char	**make_args(t_comm *com, int *args_cnt);

void	exe_cmd(char **args, int args_cnt);
int		is_blt(char **args);

t_envp	*make_envp(char **envp);

void    ft_pwd(char **args);
int		ft_cd(char **args);
void    ft_echo(char **args);// -nnnn수정해야함
int		ft_export(t_envp *my_envp, char **args, int args_cnt);
void    ft_unset(t_envp *my_envp, char **args);

#endif