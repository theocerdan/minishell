/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:18:14 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:18:15 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_shell *shell, char *each_cmd)
{
	int		pid;
	int		ret;
	char	**exec_arg;
	char	*path;

	path = get_path(shell, each_cmd);
	exec_arg = ft_split_clean(shell, each_cmd, ' ');
	int i = 0;
	while (exec_arg[i]){
		i++;
	}
	char **tab = convert_env_to_string_tab(shell);
	i = 0;
		while (tab[i])
		{
			i++;
		}
	pid = fork();
	if (pid == -1){
		perror("fork");
	}
	else if (pid > 0)
	{
		waitpid(pid, &(shell->error_return), 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (path == NULL)
			path = exec_arg[0];
		ret = execve(path, exec_arg, convert_env_to_string_tab(shell));
		if (ret == -1)
			printf("minishell: %s: command not found\n", each_cmd);
		exit(EXIT_FAILURE);
	}
}

void	execute(t_shell *shell)
{
	int		i;
	t_built	cmd;
	char	*command_to_execute;

	i = 0;
	while (i < shell->nbr_cmd)
	{
		command_to_execute = get_executable(shell, shell->tab_cmd[i]);
		cmd = get_command_type(command_to_execute);
		if (cmd.id != EXEC)
			cmd.process_ft(shell, command_to_execute);
		else {
			execute_cmd(shell, shell->tab_cmd[i]);
		}
		i++;
	}
}
