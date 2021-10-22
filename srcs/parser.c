#include "../includes/minishell.h"

int		get_number_of_commands(t_shell *shell)
{
	t_token *cmd;
	t_list 	*start;
	int		nbr_cmd;

	nbr_cmd = 1;
	start = shell->token_list;
	while (shell->token_list)
	{
		cmd = (t_token*)shell->token_list->content;
		if (cmd->type == PIPE)
			nbr_cmd++;
		shell->token_list = shell->token_list->next;
	}
	shell->token_list = start;
	return (nbr_cmd);
}

int	*get_each_cmd_lenght(t_shell *shell, int nbr_cmd)
{
	int		i;
	int		j;
	int		count;
	int		*each_cmd_lenght;

	i = 0;
	j = 0;
	count = 1;
	each_cmd_lenght = (int *)malloc((nbr_cmd + 1) * sizeof(int));
	while (shell->command_line_clean[i])
	{
		if (((shell->command_line_clean[i + 1] == ' ') && (shell->command_line_clean[i + 2] == '|')) || shell->command_line_clean[i + 1] == '\0')
		{
			each_cmd_lenght[j] = count;
			count = 0;
			j++;
		}
		if (shell->command_line_clean[i] == ' ' && shell->command_line_clean[i + 1] == '|' && shell->command_line_clean[i + 2] == ' ')
			i = i + 3;
		count++;
		i++;
	}
	return (each_cmd_lenght);
}

void	fill_cmd_array(t_shell *shell, int *each_cmd_lenght)
{
	int		i;
	int		j;
	int		milestone;

	i = 0;
	j = 0;
	milestone = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i + 1] == '|' || shell->command_line_clean[i + 1] == '\0')
		{
			shell->tab_cmd[j] = ft_substr(shell->command_line_clean, milestone, each_cmd_lenght[j]);
			milestone = i + 3;
			j++;
		}
		i++;
	}
}

char	*get_executable(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str && str[i] != ' ' && str[i] != '\0')
		i++;
	tmp = ft_substr(str, 0, i);
	return (tmp);
}

////////////////////////////////////////////////////////////////////////////

int		is_executable(char *cmd_path)
{
	struct stat	buffer;

	if (stat(cmd_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

char	*get_possible_path(char *envpath, char *cmd)
{
	char	*path;
	char	*first_part;

	path = NULL;
	first_part = NULL;
	(void)(cmd);
	if (ft_strncmp(envpath, cmd, ft_strlen(envpath)) == 0)
		path = ft_strdup(cmd);
	else
	{
		first_part = ft_strjoin(envpath, "/");
		path = ft_strjoin(first_part, cmd);
	}
	return (path);
}

char	*get_path_variable(t_shell *shell)
{
	t_list	*start;
	t_env	*env;
	char	*path_variable;

	path_variable = NULL;
	start = shell->env_vars;
	while (shell->env_vars)
	{
		env = (t_env*)shell->env_vars->content;
		if (ft_strcmp(env->key, "PATH") == 0)
			path_variable = env->value;
		shell->env_vars = shell->env_vars->next;
	}
	shell->env_vars = start;
	return (path_variable);
}

char	*get_correct_cmd_path(char *path_variables, char *each_cmd)
{
	char	**all_paths;
	char	*cmd_path;
	char	*first_part_cmd;
	int		i;

	i = 0;
	cmd_path = NULL;
	all_paths = ft_split(path_variables, ':');
	first_part_cmd = get_first_word_cmd(each_cmd);
	while (all_paths && all_paths[i])
	{
		cmd_path = get_possible_path(all_paths[i], first_part_cmd);
		if (is_executable(cmd_path))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (cmd_path);
}

char	*get_path(t_shell *shell, char *each_cmd)
{
	char	*path_variables;
	char	*correct_cmd_path;

	path_variables = get_path_variable(shell);
	correct_cmd_path = get_correct_cmd_path(path_variables, each_cmd);
	return (correct_cmd_path);
}

////////////////////////////////////////////////////////////////////////////

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
	if (pid == 0)
		execve(path, exec_arg, shell->env_tab);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->error_return = WEXITSTATUS(status);
}

void	execute_builtin(t_shell *shell, char *command_to_execute, char *each_cmd)
{
	if (!(ft_strcmp(command_to_execute, "echo\0")))
		echo(each_cmd);
	else if (!(ft_strcmp(command_to_execute, "pwd")))
		pwd();
	//else if (!(ft_strcmp(command_to_execute, "cd")))
	//	cd();
	else if (!(ft_strcmp(command_to_execute, "export")))
		export(shell, each_cmd);
	else if (!(ft_strcmp(command_to_execute, "unset")))
		unset(shell, each_cmd);
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

void	parse_command(t_shell *shell)
{
	int		*each_cmd_lenght;

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
