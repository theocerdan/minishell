#include "../includes/minishell.h"

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int     match(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
    return (0);
}

int     is_between_quotes(char *str, int i, char c)
{
    if (is_quote(c) && match(str, i, c))
		return (1);
    return (0);
}

char    *operate_quotes(char *token, int pos)
{
    char    *tmp1;
    char    *tmp2;
    int     j;
    int     i;

    j = 0;
    i = pos + 1;
    while (token[i])
    {
        if (is_quote(token[i]))
            break ;
        j++;
        i++;
    }
    tmp1 = ft_substr(token, 0, pos);
    tmp2 = ft_substr(token, pos + 1, j);
    token = ft_strjoin(tmp1, tmp2);
    //printf("tmp1:%s|\n", tmp1);
    //printf("tmp2:%s|\n", tmp2);
    return (token);
}

char    *check_if_quotes(char *each_cmd)
{
    int     i;
    char    *token;

    i  = 0;
    token = each_cmd;
    //printf("token pur:%s\n", token);
    while (token[i])
    {
        if (is_between_quotes(token, i, token[i]))
        {
            token = operate_quotes(token, i);
        }
        i++;
    }
    return (token);
}
