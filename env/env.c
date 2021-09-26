#include "../includes/minishell.h"

void setup_default_env(char **envp, t_shell *shell){
    char	*default_lst[] = {"PATH=", "HOME=", "OLDPWD=", "PWD=", "SHLVL=", NULL};
    int i = 0;
    int a = 0;
    int e = 0;
    char *key;
    while (envp[i]){
        while (default_lst[a]){
            if (strncmp(default_lst[a], envp[i], ft_strlen(default_lst[a])) == 0){
                ft_strlcpy(key, default_lst[a], ft_strlen(default_lst[a]));
                ft_create_var(key, envp[i]+ft_strlen(default_lst[a]), shell);
            }
            a++;
        }
        a = 0;
        i++;
    }
}