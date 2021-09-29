#include "../includes/minishell.h"

void	init_queue(t_shell *shell, char *command)
{
	int		i;
	char 	**splited_cmd;
	int		number_of_element;
	
	splited_cmd = ft_split(command, '|');
	number_of_element = get_size(splited_cmd);
	shell->queue = ft_safe_malloc(sizeof(t_built) * number_of_element, shell);
	i = 0;
	while (i < number_of_element)
	{
		t_cmd *cmd = ft_safe_malloc(sizeof(t_cmd), shell);
		//int (*process_ft)(char* cmd);
		cmd->id = i;
		cmd->full_cmd = splited_cmd[i];
		cmd->type = get_command_type(cmd);
		shell->queue[i] = cmd;
		i++;
	}
}

void	prompt(t_shell *shell)
{
	char 	*cmd = NULL;

	while (1)
	{
		cmd = start_prompt(cmd); // écriture d'un prompt avec path + récup commande
		if (cmd)
			add_history(cmd); // création historique pour avoir accéder aux commandes précédentes
		init_queue(shell, cmd);
		ft_create_var(cmd, cmd, shell);
		//printf("-------%s\n", get_env_value("caca", shell));
		//print_env(shell);
		if (cmd)
			free(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell *shell = NULL;

	shell = ft_safe_malloc(sizeof(shell), shell);
	shell->env_vars = NULL;
	if (argc > 1 && argv)
		ft_error("too many arguments\n");
	prompt(shell);
	ft_total_clean(shell);
	return (0);
}
