#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "libft.h"

#define CD 0
#define ENV 1
#define PWD 2
#define EXPORT 3
#define UNSET 4
#define EXIT 5
#define ECHO 6
#define EXEC 7

# define BUILTIN 42
# define LITERAL 43
# define PIPE 44
# define REDIRECT 45
# define FLAG 46
# define ENV_TOKEN 47

typedef struct	s_env
{
	char		*key;
	char		*value;
	int			visible;
}				t_env;

typedef struct	s_cmd
{
    int			id;
	int			type;
	char		*full_cmd;
} 				t_cmd;

typedef struct	s_built
{
    int			id;
    char 		*cmd;
	int 		(*process_ft)(char* cmd);
} 				t_built;

typedef struct s_token
{
	int			type;
	char		*value;
}				t_token;

typedef struct	s_shell
{
	t_list		*ptrs;
	t_list		*env_vars;
	t_cmd		**queue;
	t_list		*token_list;
	
	int			fd;
	int			error_return;
	int			nbr_cmd;
	char		*command_line_clean;
	char		**tab_cmd;
}				t_shell;

void	*ft_safe_malloc(unsigned int size, t_shell *s);
void	ft_add_to_garbage(void *ptr, t_shell *s);
int		get_command_type(t_cmd *cmd);
int 	str_equals_ignore_case(char *text_1, char *text_2);
void	exec_cmd(char *path, char **cmd, char **envp);
void 	setup_default_env(char **envp, t_shell *shell);
void	ft_clean(void *ptr);
int 	get_size(char **array);
void	ft_create_var(char *key, char *value, t_shell *shell);
void	print_all_env(t_list *lst);
void	ft_delete_var(char *target_key, t_shell *shell);
int		ft_strcmp(char *s1, char *s2);
int		env_key_exist(char *target_key, t_shell *shell);
char	*start_prompt(t_shell *shell, char *cmd);
t_env	*get_env_object(char *target_key, t_shell *shell);
void    signal_listeners(void);
void    ft_error(char *str);

int 	process_exit(char* cmd);
int 	process_cd(char* cmd);
int 	process_unset(char* cmd);
int 	process_pwd(char* cmd);
int 	process_export(char* cmd);
int 	process_env(char* cmd);
int 	process_exec(char* cmd);
int		process_echo(char *cmd);

void	ft_total_clean(t_shell *m);
void	signal_handler(int sig);
char	*create_prompt(t_shell *shell);
void	ft_clear_token(t_shell *shell);
int		define_type(char *value);
void	print_all_token(t_shell *shell);
void	tokenization(t_shell *shell, char *cmd);
void	parser(t_shell *shell);

int		is_builtin(char *value);

void	echo(char *each_cmd);
void	pwd(void);
void	export(t_shell *shell, char *each_cmd);
void	ft_exit(t_shell *shell, char *each_cmd);
void    unset(t_shell *shell, char *each_cmd);

void    init_env(t_shell *shell, char **envp);

int		get_argc(char *str);
char	*get_first_arg(char *each_cmd);
int		ft_isnumber(char *s);

#endif