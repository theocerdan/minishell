#include "../includes/minishell.h"

void	ft_env(t_shell *shell, char *cmd)
{
	(void)(cmd);
	print_all_env(shell->env_vars);
}
