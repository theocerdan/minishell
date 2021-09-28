#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
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

// https://github.com/AzodFR/minishell

typedef struct	s_env
{
	char		*key;
	char		*value;
	int			visible;
}				t_env;

typedef struct	s_built
{
    int			id;
    char 		*cmd[10];
	int 		(*process_ft)(t_shell *shell, char* cmd);
} 				t_built;

typedef struct	s_shell
{
	t_list		*ptrs;
	t_list		*env_vars;
	t_built		*queue;
}				t_shell;

void	*ft_safe_malloc(unsigned int size, t_shell *s);
void	ft_add_to_garbage(void *ptr, t_shell *s);
int 	get_correct_built(char *text, int (**process_ft)(t_shell *shell, char* cmd));
int 	equals_ignore_case(char *text_1, char *text_2);
char 	*get_next_word(char *text, t_shell *shell);
char	*get_absolute_path(char *cmd);
void	exec_cmd(char *path, char **cmd, char **envp);
void 	setup_default_env(char **envp, t_shell *shell);
void	ft_clean(void *ptr);
void	*ft_create_var(char *key, char *value, t_shell *s);
void	*get_env_value(char *name, t_shell *s);
int 	get_size(char **array);

char	*start_prompt(char *cmd);

void    ft_error(char *str);

int 	process_exit(t_shell *shell, char* cmd);
int 	process_cd(t_shell *shell, char* cmd);
int 	process_echo(t_shell *shell, char* cmd);
int 	process_unset(t_shell *shell, char* cmd);
int 	process_pwd(t_shell *shell, char* cmd);
int 	process_export(t_shell *shell, char* cmd);
int 	process_env(t_shell *shell, char* cmd);

#endif