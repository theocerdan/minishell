#include "../includes/minishell.h"

int		is_builtin(char *value)
{
	if (!value)
		return (0);

		// || !(ft_strcmp(value, "exit")))
	if (get_command_type(value).id != EXEC)
		return (1);
	return (0);
}

int		is_double_quote(char *value)
{
	int last_i;

	last_i = ft_strlen(value);
	if (!value)
		return (0);
	if (value[last_i - 1] == '"' && value[0] == '"')
		return (1);
	return (0);
}

int		is_single_quote(char *value)
{
	int last_i;

	last_i = ft_strlen(value);
	if (!value)
		return (0);
	if (value[last_i - 1] == '\'' && value[0] == '\'')
		return (1);
	return (0);
}

int		is_operator(char *value)
{
	if (!(ft_strcmp(value, "|")) || !(ft_strcmp(value, ">"))|| !(ft_strcmp(value, "<")) || !(ft_strcmp(value, ">>")) || !(ft_strcmp(value, "<<")))
		return (1);
	return (0);
}

int		is_env(char *value)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if ((value[i] >= 65 && value[i] <= 90) || value[i] == 36)
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
