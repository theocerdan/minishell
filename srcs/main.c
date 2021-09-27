#include "../includes/minishell.h"

static char	*join_prompt_element(char *name, char *pwd, char *end)
{
	char	*tmp;
	char	*prompt;

	tmp = ft_strjoin(name, pwd);
	prompt = ft_strjoin(tmp, end);
	free(name);
	free(tmp);
	free(pwd);
	free(end);
	return (prompt);
}


char	*get_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	return (getcwd(buffer, 0));
}

char	*create_prompt(void)
{
	char	*pwd;
	char	*name;
	char	*end;
	char	*result;

	pwd = get_pwd();
	name = ft_strdup("Minishell");
	end = ft_strdup("$ ");
	result = join_prompt_element(name, pwd, end);
	return (result);
}

void	start_prompt()
{
	char	*prompt;

	prompt = create_prompt();
	readline(prompt);
	free(prompt);
}

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
	// ecriture d'un prompt
	char	*input;
	while (1)
	{
		input = NULL;
		start_prompt();
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
