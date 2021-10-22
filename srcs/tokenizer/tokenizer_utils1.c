#include "../includes/minishell.h"

int		is_builtin(char *value)
{
	if (!value)
		return (0);
	if (!(ft_strcmp(value, "echo\0")) || !(ft_strcmp(value, "cd\0")) || !(ft_strcmp(value, "pwd")) || !(ft_strcmp(value, "export")) || !(ft_strcmp(value, "unset")) || !(ft_strcmp(value, "env")) || !(ft_strcmp(value, "exit")))
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
