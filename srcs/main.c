#include "../includes/minishell.h"

void	prompt(t_shell *shell)
{
	char 	*cmd = NULL;

	while (1)
	{
		cmd = start_prompt(shell, cmd); // écriture d'un prompt avec path + récup commande
		if (cmd)
			add_history(cmd); // création historique pour avoir accéder aux commandes précédentes
		tokenization(shell, cmd);
		if (shell->command_line_clean)
			parser(shell);
		ft_lstclear(&(shell->token_list), &free);
		if (cmd)
			free(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell *shell;

	shell = NULL;
	shell = ft_safe_malloc(sizeof(t_shell), shell);
	shell->command_line_clean = NULL;
	shell->env_vars = NULL;
	shell->token_list = NULL;
	shell->error_return = 0;
	if (argc > 1 && argv)
		ft_error("too many arguments\n");
	init_env(shell, envp);
	prompt(shell);
	ft_total_clean(shell);
	return (0);
}
