#include "../includes/minishell.h"

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int     match(char *str, int i, char c)
{
	int     count;

	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

int     is_between_quotes(char *str, int i, char c)
{
	if (is_quote(c) && match(str, i, c))
		return (1);
	return (0);
}

char    *operate_quotes(char *str)
{
	char    *tmp1;
	char    *tmp2;
	int		pos;
	int     j;
	int     i;

	i = 0;
	pos = 0;
	while (str[i])
	{
		if (is_between_quotes(str, i, str[i]))
		{
			pos = i;
			break ;
		}
		i++;
	}
	j = 0;
	i = pos + 1;
	while (str[i])
	{
		if (is_quote(str[i]) && str[i + 1] == '\0')
			break ;
		j++;
		i++;
	}
	tmp1 = ft_substr(str, 0, pos);
	tmp2 = ft_substr(str, pos + 1, j);
	str = ft_strjoin(tmp1, tmp2);
	return (str);
}

int		still_has_quote(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*resolve_quote_issue(char *str)
{
	char	*result;

	result = str;
	do
	{
		result = operate_quotes(result);
	} while (still_has_quote(result));
	return (result);
}

char    *check_if_quotes(char *each_cmd)
{
	int     i;
	char    *str;

	str = each_cmd;
	i = 0;
	while (str[i])
	{
		if (is_between_quotes(str, i, str[i]))
			str = resolve_quote_issue(str);
		i++;
	}
	return (str);
}
