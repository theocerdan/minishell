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
		cmd->id = i;
		cmd->full_cmd = splited_cmd[i];
		cmd->type = get_command_type(cmd);
		shell->queue[i] = cmd;
		i++;
	}
}

void    init_env_lst(t_shell *shell, char **envp)
{
    int		i;
	char	**split;
	char	*key;
	char	*value;

	i = 0;
    while (envp[i])
	{
        split = ft_split(envp[i], '=');
        key = split[0];
        value = split[1];
        ft_create_var(key, value, shell);
        i++;
    }
}

void    init_env_tab(t_shell *shell, char **envp)
{
    int		i;

	i = 0;
	while (envp[i])
		i++;
	if (!(shell->env_tab = ft_safe_malloc(sizeof(char *) * (i + 2), shell)))
		exit(0);
	i = -1;
	while (envp[++i])
	{
		if (!(shell->env_tab[i] = ft_safe_malloc(ft_strlen(envp[i]) + 100, shell)))
			exit(0);
		shell->env_tab[i] = envp[i];
	}
	shell->env_tab[i] = NULL;
}

void	init_env(t_shell *shell, char **envp)
{
	init_env_lst(shell, envp);
	init_env_tab(shell, envp);
}
