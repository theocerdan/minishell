#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#define CD 0
#define ENV 1
#define PWD 2
#define EXPORT 3
#define UNSET 4
#define EXIT 5
#define ECHO 6
#define EXEC 7

#define BUILTIN 42
#define LITERAL 43
#define PIPE 44
#define REDIRECT 45
#define FLAG 46
#define ENV_TOKEN 47

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
	char		**env_tab;
	t_cmd		**queue;
	t_list		*token_list;
	
	int			fd;
	int			error_return;
	int			nbr_cmd;
	char		*command_line_clean;
	char		**tab_cmd;
}				t_shell;

int 	process_exit(char* cmd);
int 	process_cd(char* cmd);
int 	process_unset(char* cmd);
int 	process_pwd(char* cmd);
int 	process_export(char* cmd);
int 	process_env(char* cmd);
int 	process_exec(char* cmd);
int		process_echo(char *cmd);
int		get_command_type(t_cmd *cmd);
int 	str_equals_ignore_case(char *text_1, char *text_2);
void	exec_cmd(char *path, char **cmd, char **envp);

/* env_manager.c */

t_env	*get_env_object(char *target_key, t_shell *shell);
int		env_key_exist(char *target_key, t_shell *shell);
void	ft_delete_var(char *target_key, t_shell *shell);
void	ft_create_var(char *key, char *value, t_shell *shell);

/* ft_prompt.c */

char	*start_prompt(t_shell *shell, char *cmd);

/* env_utils.c */

void	print_all_env(t_list *lst);

/* parser.c */

void	parser(t_shell *shell);

/* ft_echo.c */

void	ft_echo(char *each_cmd);

/* ft_pwd.c */

void	ft_pwd(void);

/* ft_export.c */

void	ft_export(t_shell *shell, char *each_cmd);

/* ft_exit.c */

void	ft_exit(t_shell *shell, char *each_cmd);

/* ft_unset.c */

void    ft_unset(t_shell *shell, char *each_cmd);

/* init.c */

void	init_env(t_shell *shell, char **envp);

/* utils_builtins.c */

int		get_argc(char *str);
char	*get_first_arg(char *each_cmd);
char	*get_first_word_cmd(char *each_cmd);
int		ft_isnumber(char *s);

/* signal.c */

void	signal_handler(int sig);
void    signal_listeners(void);
void	define_exec_signals(void);

/* execute.c */

void	execute(t_shell *shell);

/* execute_utils1.c */

char	*get_executable(char *str);

/* execute_utils2.c */

char	*get_path(t_shell *shell, char *each_cmd);

/* tokenizer.c */

void	tokenization(t_shell *shell, char *cmd);

/* tokenizer_utils1.c */

int		is_builtin(char *value);
int		is_operator(char *value);
int		is_env(char *value);
int		is_flag(char *value);
int		ft_isblank(int c);

/* tokenizer_utils2.c */

int     no_need_to_tokenization(char *cmd);
int		define_type(char *value);
int		is_between_blanks(char after_char, char before_char);
int		no_blanks_around_operator(char current_char, char after_char, char before_char);

/* tokenizer_utils3.c */

void	print_all_token(t_shell *shell);
void    init_token(t_shell *shell, char *cmd);

/* tokenizer_utils4.c */

char	*insert_spaces(char *line, char operator_pointer, int off_set);

/* utils.c */

int	ft_strcmp(char *s1, char *s2);
int	get_size(char **array);

/* ft_error.c */

void    ft_error(char *str);

/* ft_memory_cleaner2000.c */

void	ft_clean(void *ptr);
void	ft_add_to_garbage(void *ptr, t_shell *s);
void	ft_total_clean(t_shell *m);
void	*ft_safe_malloc(unsigned int size, t_shell *s);

/* quotes.c */

char    *check_if_quotes(char *each_cmd);

#endif
