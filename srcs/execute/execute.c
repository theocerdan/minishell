#include "../includes/minishell.h"

void	execute_cmd(t_shell *shell, char *each_cmd)
{
	int		pid;
	int		status;
	char	**exec_arg;
	char	*path;

	path = get_path(shell, each_cmd);
	exec_arg = ft_split(each_cmd, ' ');
	pid = fork();
	define_exec_signals();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(path, exec_arg, shell->env_tab) == -1)
		{
			printf("execve: %s\n", path);
			perror("shell");
		}
		exit(EXIT_FAILURE);
	}
}

void	execute_builtin(t_shell *shell, char *command_to_execute, char *each_cmd)
{
	if (!(ft_strcmp(command_to_execute, "echo\0")))
		ft_echo(each_cmd);
	else if (!(ft_strcmp(command_to_execute, "pwd")))
		ft_pwd();
	//else if (!(ft_strcmp(command_to_execute, "cd")))
	//	cd();
	else if (!(ft_strcmp(command_to_execute, "export")))
		ft_export(shell, each_cmd);
	else if (!(ft_strcmp(command_to_execute, "unset")))
		ft_unset(shell, each_cmd);
	else if (!(ft_strcmp(command_to_execute, "exit")))
		ft_exit(shell, each_cmd);
	else if (!(ft_strcmp(command_to_execute, "env")))
		print_all_env(shell->env_vars);
}

void	execute(t_shell *shell)
{
	int		i;
	char	*command_to_execute;

	/*if (shell->tab_cmd[i])
	{
		if (ft_strchr(shell->tab_cmd[i], '='))
			set_local_variable(shell->tab_cmd[i], &i);
	}*/
	i = 0;
	while (i < shell->nbr_cmd)
	{
		command_to_execute = get_executable(shell->tab_cmd[i]);
		if (is_builtin(command_to_execute))
			execute_builtin(shell, command_to_execute, shell->tab_cmd[i]);
		else
			execute_cmd(shell, shell->tab_cmd[i]);
		i++;
	}
}
