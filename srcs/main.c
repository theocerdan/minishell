#include "../includes/minishell.h"

void	prompt(void)
{
	//char	*buffer = NULL;
	//size_t	buf_size = 2048;
	//int		i;
	//char 	**cmd;
	//char	*built_name;
	//char	*built_path;
	//int		built_id;
	//int 	(*process_ft)(t_shell *shell, char* cmd);
	//t_shell *shell = ft_safe_malloc(sizeof(t_shell), NULL);
	
	// alloc buffer qui stockera la commande entree par l'user
	//buffer = ft_safe_malloc(sizeof(char) * buf_size, shell);
	//setup_default_env(envp, shell);
	// écriture d'un prompt
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		cmd = start_prompt(cmd); // écriture d'un prompt avec path + récup commande taper
		if (cmd)
			add_history(cmd); // création historique pour avoir acceder aux commandes précédentes
		printf("command: %s\n", cmd);
		if (cmd)
			free(cmd);
	}
	/*write(1, "$> ", 3);
	// lecture de STDIN en boucle
	while (getline(&buffer, &buf_size, stdin) > 0) //mettre notre get_next_line
	{
		i = 0;
		cmd = ft_split(buffer, ';');
		while (cmd[i])
		{
			built_name = get_next_word(cmd[i], shell);
			built_id = get_correct_built(built_name, &process_ft);
			built_path = get_absolute_path(built_name);
			//ft_create_var("key", "valizi", shell);
			//printf("---- %s\n", (char*)get_env_value("key", shell));
			if (built_id >= 0)
				process_ft(shell, cmd[i]);
			else
			{
				//printf("path -> %s\n", built_path);
				//exec_cmd(built_path, &built_name, envp);
			}
			i++;
		}
		write(1, "$> ", 3);
	}
	printf("exit \n");
	free(buffer);*/
}

int	main(int argc, char **argv)
{
	if (argc > 1 && argv)
		ft_error("too many arguments\n");
	prompt();
	return (0);
}