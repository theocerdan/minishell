#include "../includes/minishell.h"

void	parse_command(t_shell *shell)
{
	int		*each_cmd_lenght;

	if (shell->command_line_clean == NULL)
		return ;
	if (have_vaguellette(shell))
		resolve_vaguellette(shell);
	shell->command_line_clean = check_if_quotes(shell->command_line_clean);
	if (have_env_variables(shell))
		resolve_replace_key_to_value_env(shell);
	shell->nbr_cmd = get_number_of_commands(shell);
	each_cmd_lenght = get_each_cmd_lenght(shell, shell->nbr_cmd);
	shell->tab_cmd = (char **)malloc((shell->nbr_cmd + 1) * sizeof(char *));
	fill_cmd_array(shell, each_cmd_lenght);
	execute(shell);
}

void	parser(t_shell *shell)
{
	shell->fd = 0;
	parse_command(shell);
	if (shell->fd != 0)
		close(shell->fd);
}
