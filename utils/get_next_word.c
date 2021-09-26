#include "../includes/minishell.h"

char *get_next_word(char *text, t_shell *shell){
    int i;
    int a;
    int len;
    int stop;
    char *res;

    len = 0;
    i = 0;
    a = 0;
    while (!ft_isprint(text[i]) && ft_strlen(text) > i)
        i++;
    while (ft_isprint(text[i+len]))
        len++;
    res = ft_safe_malloc(sizeof(char)*len, shell);
    stop = i + len;
    while (i < stop)
        res[a++] = text[i++];
    res[a] = '\0';
    text = text + len;
    return res;
}