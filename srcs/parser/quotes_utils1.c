#include "../includes/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	match(char *str, int i, char c)
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
