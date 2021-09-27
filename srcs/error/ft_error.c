#include "../includes/minishell.h"

void	ft_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	exit(0);
}
