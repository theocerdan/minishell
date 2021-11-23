/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:45:45 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 16:45:47 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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
#define DOUBLE_QUOTE 48
#define SINGLE_QUOTE 49

typedef struct s_env
{
	char *key;
	char *value;
	int visible;
} t_env;

typedef struct s_cmd
{
	int id;
	int type;
	char *full_cmd;
} t_cmd;

typedef struct s_token
{
	int type;
	char *value;
} t_token;

typedef struct s_shell
{
	t_list *ptrs;
	t_list *env_vars;
	char **env_tab;
	t_cmd **queue;
	t_list *token_list;
	int fd;
	int error_return;
	int nbr_cmd;
	char *command_line_clean;
	char **tab_cmd;
} t_shell;

typedef struct s_built
{
	int id;
	char *cmd;
	void (*process_ft)(t_shell *shell, char *cmd);
} t_built;

/* env_manager.c */

t_env *get_env_object(char *target_key, t_shell *shell);
int	env_value_exist(char *target_key, t_shell *shell);
int env_key_exist(char *target_key, t_shell *shell);
void ft_delete_var(char *target_key, t_shell *shell);
void ft_create_var(char *key, char *value, t_shell *shell);
int	env_len(t_shell *shell);

/* ft_prompt.c */

char *start_prompt(t_shell *shell, char *cmd);

/* env_utils.c */

void ft_env(t_shell *shell, char *cmd);
void print_all_env(t_list *lst);
char** convert_env_to_string_tab(t_shell *shell);

/* parser.c */

void parser(t_shell *shell);

/* ft_echo.c */

void ft_echo(t_shell *shell, char *cmd);

/* ft_pwd.c */

void ft_pwd(t_shell *shell, char *cmd);

/* ft_export.c */

void ft_export(t_shell *shell, char *cmd);

/* ft_cd.c */

void ft_cd(t_shell *shell, char *cmd);

/* ft_exit.c */

void ft_exit(t_shell *shell, char *cmd);

/* ft_unset.c */

void ft_unset(t_shell *shell, char *cmd);

/* init.c */

void init_env(t_shell *shell, char **envp);

/* utils_builtins.c */

int get_argc(char *str);
char *get_first_arg(char *each_cmd);
char *get_first_word_cmd(char *each_cmd);
int ft_isnumber(char *s);

/* signal.c */

void define_exec_signals(void);
void define_input_signals(void);

/* execute.c */

void execute_cmd(t_shell *shell, char *each_cmd);
void execute(t_shell *shell);

/* execute_utils1.c */

t_built get_command_type(char *cmd);
char *get_executable(char *str);

/* execute_utils2.c */

char *get_path(t_shell *shell, char *each_cmd);

/* tokenizer.c */

int tokenization(t_shell *shell, char *cmd);

/* tokenizer_utils1.c */

int is_builtin(char *value);
int is_operator(char *value);
int is_env(char *value);
int is_flag(char *value);

/* tokenizer_utils2.c */

int is_double_quote(char *value);
int is_single_quote(char *value);
int no_need_to_tokenization(char *cmd);
int define_type(char *value);
int is_between_blanks(char after_char, char before_char);
int no_blanks_around_operator(char current_char,
							  char after_char, char before_char);

/* tokenizer_utils3.c */

void print_all_token(t_shell *shell);
void init_token(t_shell *shell, char *cmd);

/* tokenizer_utils4.c */

int ft_isblank(int c);
char *insert_spaces(char *line, char operator_pointer, int off_set, t_shell *shell);

/* utils.c */

int ft_strcmp(char *s1, char *s2);
int get_size(char **array);
int ft_is_special(char c);
int ft_is_lowercase(char c);
int ft_is_uppercase(char c);
char *lower_str(char *str);
int count_spacing(char c, char *text);

/* ft_error.c */

void ft_error(char *str);

/* ft_memory_cleaner2000.c */

void ft_clean(void *ptr);
void ft_add_to_garbage(void *ptr, t_shell *s);
void ft_total_clean(t_shell *m);
void *ft_safe_malloc(unsigned int size, t_shell *s);

/* quotes.c */

int is_quote(char c);
char *check_if_quotes(char *each_cmd);

/* quotes_utils1.c */

int is_between_quotes(char *str, int i, char c);
int still_has_quote(char *str);
int quote_hole(char *str, char c);

/* quotes_utils2.c */

char *operate_quotes(char *str);
char *special_case_quotes(char *str);

/* quotes_utils3.c */

char get_quote_to_remove(char *str);

/* vaguellette.c */

int have_vaguellette(t_shell *shell);
void resolve_vaguellette(t_shell *shell);

/* parse_env_key_utils1.c */

int have_env_variables(t_shell *shell);
int next_word_env_key(t_shell *shell);
char *get_replacement_env_key(t_shell *shell);

/* parse_env_key.c */

int dollar_plus_number(t_shell *shell);
char *get_tmp2(t_shell *shell);
void resolve_replace_key_to_value_env(t_shell *shell);

/* parser_utils1.c */

int get_number_of_commands(t_shell *shell);
int *get_each_cmd_lenght(t_shell *shell, int nbr_cmd);
void fill_cmd_array(t_shell *shell, int *each_cmd_lenght);

char *get_tmp2_dollar_plus_number(t_shell *shell);
char *replace_dollar_plus_number(t_shell *shell);
void resolve_dollar_plus_number(t_shell *shell);
int dollar_plus_number(t_shell *shell);
int		is_index_is_between_quote(int index, t_shell *shell);

char    *ft_strdup_clean(t_shell *shell, const char *s1);
char    *ft_strjoin_clean(t_shell *shell, const char *s1, const char *s2);
char    *ft_substr_clean(t_shell *shell, char const *s, unsigned int start, size_t len);
char    **ft_split_clean(t_shell *shell, char const *s, char c);
#endif
