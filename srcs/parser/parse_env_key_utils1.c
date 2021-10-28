#include "../includes/minishell.h"

int		have_env_variables(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$' && next_word_env_key(shell))
			return (1);
		else if (shell->command_line_clean[i] == '$' && shell->command_line_clean[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}
