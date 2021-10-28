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
		if (str[i++] == c)
			count++;
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
	char	*tmp3;
	int		pos;
	int     j;
	int     i;

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

int		quote_hole(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && str[i] == c)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

int		has_two_type_quotes(char *str)
{
	int		i;
	int		sql_qts;
	int		dbl_qts;

	i = 0;
	sql_qts = 0;
	dbl_qts = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sql_qts++;
		else if (str[i] == '\"')
			dbl_qts++;
		i++;
	}
	if (sql_qts != 0 && dbl_qts != 0 && sql_qts % 2 == 0 && dbl_qts % 2 == 0)
		return (1);
	return (0);
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

char	*resolve_special_case_quotes(char *str)
{
	char	*result;

	result = str;
	do
	{
		result = special_case_quotes(result);
	} while (has_two_type_quotes(result));
	return (result);
}

char    *check_if_quotes(char *each_cmd)
{
	int     i;
	char    *str;

	i = 0;
	str = each_cmd;
	while (str[i])
	{
		if (quote_hole(str, str[i]))
		{
			printf("Error : need a quote to finish the line.\n");
			exit(0);
		}
		else if (is_between_quotes(str, i, str[i]))
			str = resolve_quote_issue(str);
		else if (has_two_type_quotes(str))
		{
			str = resolve_special_case_quotes(str);
			break ;
		}
		i++;
	}
	return (str);
}
