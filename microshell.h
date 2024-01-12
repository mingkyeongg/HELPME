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
	char			*key;
	char			*value;
	int				state;
	struct s_envp	*next;
}	t_envp;

typedef struct s_data
{
	int 	in_fd; 
	int 	out_fd;
	char	**args;
	int		arg_cnt;
	pid_t	*pid;
	int		i_pid;
	struct s_data	*next;
}	t_data;



#define STR 0
#define PIPE 1
#define DLESS 2 // <<
#define LESS 3 // <
#define DGREAT 4 // >>
#define GREAT 5 // >


#define HAS_EQUAL 10 // envp_state
#define NO_EQUAL 11

// need define num change
#define REMOVE 6
#define LEAVE 7
#define QUOTED 8
#define UNQUOTED 9
#define CONTINUE 10
#define SINGLE 11
#define DOUBLE 12


#define SYNTAX_ERR 258

/* tokenize */

int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

char	**put_args(char **args, char *token, int cnt);
char	**make_args(t_comm *com, int *args_cnt);

void	exe_cmd(t_comm *cmd, t_envp *my_envp, char **args, int args_cnt);
int		is_blt(char **args);

t_envp	*make_envp(char **envp);

t_comm	*ft_redirect_handling(t_comm *cmd);
void	exe_redirection(char *arg, int type);

void	run_command(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg);
char	**make_args_fork(t_comm *cmd, int *args_cnt);

void	command_use_fork(t_comm *cmd, t_envp *my_envp, t_data *ofd_arg);

void    ft_pwd(char **args);
int		ft_cd(char **args);
void    ft_echo(char **args);
void	ft_export(t_envp *my_envp, char **args, int args_cnt);
void    ft_unset(t_envp *my_envp, char **args);
void    ft_env(t_envp *my_envp);
void    ft_exit(t_comm *cmd, char **args);
void	ft_execve(char **args);

void	add_envp(t_envp *my_envp, char** envp, int i_line);

void	print_my_envp(t_envp *my_envp);
void	print_args(char **args);

char	*find_cmd_path(char *command);

/* tokenizing */

/* tokenize.c */

char *mk_strdup(int start, int end, char *line, int flag);
void split_line(char *line, t_comm **cmd);

/* put_on_list.c */
int prev_check(t_comm **cmd, char *token, int type);
void push_back(t_comm **cmd, char *token, int type);

/* find syn_err.c */
int find_syntax_err(char *buf);
int only_redirec(char *buf);
int pipe_at_the_end(char *buf);

/* pre_processing.c */
int tokenizing(char *line, t_comm **cmd, int i);
int read_input(t_comm **cmd);
void free_list(t_comm *cmd);

/* token_utils.c */
int is_del(char *line);
int is_space(char a);
int is_dquotes(char a);
int is_squotes(char a);
int is_redirect(char a);

/* token_utils_two.c */
int is_pipe(char a);
int is_env(char a);

/* process_delimited.c */
char *find_delimited(char *token, t_comm **cmd, int i, int start);
void push_back_delimited(char *token, int *index, t_comm **cmd, int *start);
void distinguishing_redirec(char *new_token, int flag, t_comm **cmd);
void process_prev_str(char *token, int start, int index, t_comm **cmd);

/* search_dollar_env.c */
int check_dless(t_comm *cmd);
char *search_env_name(char *str);
int return_last_dollar_pos(char *str);
char* find_last_dollar(char* str);
void find_last_pos(char **str);

/* process_remove.c */
void split_env(char **token, t_comm **cmd);
void remove_dollar(char *str);
void remove_undefined_env(char **token);
void remove_quotes(char **str, int start) ;

/* process_dollar.c */
void connecting_string(char **token, char *var_value, char *var_name, char *dollar_pos);
void processing_after_dless(char **token);
void put_in_env(char **token, char **dollar_pos);
int process_env_var(char **token, t_comm **cmd, int flag, char *line);

/* work_inside_quotes.c */
void process_in_quotes(char *line, int *index, int *start, t_comm **cmd);
void push_quote_string(t_comm **cmd, char *line, int index, char **temp);
char  *process_dquo(char *line, int *i, int *start, t_comm **cmd);
char  *process_squo(char *line, int *i, int *start, t_comm **cmd);

/* utils_quotes.c */
void process_natural_str(char **temp, t_comm **cmd, char *line);
void index_update(int *i, int *start, int quote_pos);
void free_temp(char **temp, char **quo_str);

#endif