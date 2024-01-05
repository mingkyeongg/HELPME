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

typedef struct s_data
{
	int 	in_fd; 
	int 	out_fd;
	char	**arv;
	struct s_data	*next;
}	t_data;


#define STR 0
#define PIPE 1
#define DLESS 2 // <<
#define LESS 3 // <
#define DGREAT 4 // >>
#define GREAT 5 // >

#define REMOVE 6
#define LEAVE 7
#define QUOTED 8
#define UNQUOTED 9
#define CONTINUE 10
#define SINGLE 11
#define DOUBLE 12

#define SYNTAX_ERR 258

/* tokenize */
void split_line(char *line, t_comm **cmd);
char *mk_strdup(int start, int end, char *line, int flag);
int process_env_var(char **token, t_comm **cmd, int flag, char *line);
void push_back(t_comm **cmd, char *token, int type);

int is_space(char a);
int is_dquotes(char a);
int is_squotes(char a);
int is_del(char *line);
int is_env(char a);
int only_space(char *buf);

int find_syntax_err(char *buf);


char  *process_squo(char *line, int *i, int *start, t_comm **cmd);
char  *process_dquo(char *line, int *i, int *start, t_comm **cmd);
void process_natural_str(char **temp, t_comm **cmd, char *line);
void push_quote_string(t_comm **cmd, char *line, int index, char **temp);
void process_in_quotes(char *line, int *index, int *start, t_comm **cmd);



void push_back_delimited(char *token, int *index, t_comm **cmd, int *start);
void process_prev_str(char *token, int start, int index, t_comm **cmd);
char *find_delimited(char *token, t_comm **cmd, int i, int start);
char* find_last_dollar(char* str);
void remove_undefined_env(char **token);
int return_last_dollar_pos(char *str);



#endif