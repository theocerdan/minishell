#include "../includes/minishell.h"

char	*get_executable(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str && str[i] != ' ' && str[i] != '\0')
		i++;
	tmp = ft_substr(str, 0, i);
	return (tmp);
}
