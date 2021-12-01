/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:22:50 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:22:51 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_possible_path(t_shell *shell, char *envpath, char *cmd)
{
	char	*path;
	char	*first_part;

	path = NULL;
	first_part = NULL;
	(void)(cmd);
	if (ft_strncmp(envpath, cmd, ft_strlen(envpath)) == 0)
		path = ft_strdup_clean(shell, cmd);
	else
	{
		first_part = ft_strjoin_clean(shell, envpath, "/");
		path = ft_strjoin_clean(shell, first_part, cmd);
	}
	return (path);
}

char	*get_correct_cmd_path(char *path_variables, char *each_cmd,
	t_shell *shell)
{
	char	**all_paths;
	char	*cmd_path;
	char	*first_part_cmd;
	int		i;

	i = 0;
	cmd_path = NULL;
	all_paths = ft_split_clean(shell, path_variables, ':');
	first_part_cmd = get_first_word_cmd(shell, each_cmd);
	while (all_paths && all_paths[i])
	{
		cmd_path = get_possible_path(shell, all_paths[i], first_part_cmd);
		if (is_executable(cmd_path))
			break ;
		ft_add_to_garbage(cmd_path, shell);
		cmd_path = NULL;
		i++;
	}
	return (cmd_path);
}

char	*get_path(t_shell *shell, char *each_cmd)
{
	char	*path_variables;
	char	*correct_cmd_path;

	if (env_key_exist("PATH", shell))
		path_variables = get_env_object("PATH", shell)->value;
	else
		path_variables = ft_strdup_clean(shell, "");

	correct_cmd_path = get_correct_cmd_path(path_variables, each_cmd, shell);
	return (correct_cmd_path);
}
