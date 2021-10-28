#include "../includes/minishell.h"

int	is_executable(char *cmd_path)
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

char	*get_path(t_shell *shell, char *each_cmd)
{
	char	*path_variables;
	char	*correct_cmd_path;

	path_variables = get_path_variable(shell);
	correct_cmd_path = get_correct_cmd_path(path_variables, each_cmd);
	return (correct_cmd_path);
}
