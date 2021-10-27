#include "../includes/minishell.h"

int     no_need_to_tokenization(char *cmd)
{
	int		i;

	if (!cmd)
		return (0);
	if (cmd[0] == '\0')
		return (1);
	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
	{
		if (cmd[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		define_operator(char *value)
{
	if (!(ft_strcmp(value, "|")))
		return (PIPE);
	if (!ft_strcmp(value, ">") || !ft_strcmp(value, "<") || !ft_strcmp(value, ">>") || !ft_strcmp(value, "<<"))
		return (REDIRECT);
	return (0);
}

int		define_type(char *value)
{
	if (is_builtin(value))
		return (BUILTIN);
	else if (is_double_quote(value))
		return (DOUBLE_QUOTE);
	else if (is_single_quote(value))
		return (SINGLE_QUOTE);
	else if (is_operator(value))
		return (define_operator(value));
	else if (is_env(value))
		return (ENV_TOKEN);
	else
		return (LITERAL);
	return (0);
}

int	is_between_blanks(char after_char, char before_char)
{
	if ((ft_isblank(before_char) && (ft_isblank(after_char))))
		return (1);
	return (0);
}

int	no_blanks_around_operator(char current_char, char after_char, char before_char)
{
	if ((current_char == '|') && !(is_between_blanks(after_char, before_char)))
		return (1);
	return (0);
}
