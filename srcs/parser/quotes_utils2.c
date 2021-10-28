#include "../includes/minishell.h"

char	*operate_quotes(char *str)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		pos;
	int		j;
	int		i;

	i = 0;
	j = 0;
	pos = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			break ;
		i++;
	}
	pos = i;
	i = pos + 1;
	while (str[i])
	{
		if (is_quote(str[i]) && (str[i + 1] == '\0'))
			break ;
		j++;
		i++;
	}
	tmp1 = ft_substr(str, 0, pos);
	tmp2 = ft_substr(str, pos + 1, j);
	tmp3 = ft_strjoin(tmp1, tmp2);
	return (tmp3);
}

char	get_quote_to_remove(char *str)
{
	int		i;
	char	to_remove;

	i = 0;
	to_remove = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			to_remove = '\'';
			break ;
		}
		else if (str[i] == '\"')
		{
			to_remove = '\"';
			break ;
		}
		i++;
	}
	return (to_remove);
}

char	*special_case_quotes(char *str)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	char	*result;
	char	to_remove;
	int		lenght_rest;
	int		pos;
	int		i;
	int		j;

	tmp = str;
	to_remove = get_quote_to_remove(tmp);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == to_remove)
			break ;
		i++;
	}
	tmp1 = ft_substr(tmp, 0, i);
	i++;
	pos = i;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == to_remove && !is_quote(tmp[i + 1]))
			break ;
		i++;
		j++;
	}
	tmp2 = ft_substr(str, pos, j);
	tmp3 = ft_strjoin(tmp1, tmp2);
	pos = i + 1;
	lenght_rest = 0;
	while (tmp[i++])
		lenght_rest++;
	tmp4 = ft_substr(tmp, pos, lenght_rest);
	result = ft_strjoin(tmp3, tmp4);
	return (result);
}
