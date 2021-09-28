#include "../includes/minishell.h"

void	prompt(t_shell *shell)
{
	char 	*cmd = NULL;
	char 	**splited_cmd;

	while (1)
	{
		cmd = start_prompt(cmd); // écriture d'un prompt avec path + récup commande taper
		if (cmd)
			add_history(cmd); // création historique pour avoir acceder aux commandes précédentes
		
		splited_cmd = ft_split(cmd, '|');
		int number_of_element = get_size(splited_cmd);
		//shell->queue = ft_safe_malloc(sizeof(t_built) * number_of_element, shell);
		//shell->queue = splited_cmd;
		printf("command: %s number of element in queue %d\n", cmd, number_of_element);
		if (cmd)
			free(cmd);
	}
}

int	main(int argc, char **argv)
{
	t_shell *shell = NULL;

	shell = ft_safe_malloc(sizeof(shell), shell);

	if (argc > 1 && argv)
		ft_error("too many arguments\n");
	prompt(shell);
	return (0);
}
