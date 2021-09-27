#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define CD 0
#define ENV 1
#define PWD 2
#define EXPORT 3
#define UNSET 4
#define EXIT 5
#define ECHO 6

// https://github.com/AzodFR/minishell

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				visible;
}					t_env;

typedef struct {
	t_list		*ptrs;
	t_list		*env_vars;
}	t_shell;

typedef struct {
    int id;
    char *cmd[10];
	int (*process_ft)(t_shell *shell, char* cmd);
} t_built;

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

int 	process_exit(t_shell *shell, char* cmd);
int 	process_cd(t_shell *shell, char* cmd);
int 	process_echo(t_shell *shell, char* cmd);
int 	process_unset(t_shell *shell, char* cmd);
int 	process_pwd(t_shell *shell, char* cmd);
int 	process_export(t_shell *shell, char* cmd);
int 	process_env(t_shell *shell, char* cmd);

/* libft */
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lts, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void*(*f)(void *), void(*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void        	ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putstr(char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			*ft_strrchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_tolower(int c);
int				ft_toupper(int c);

#endif