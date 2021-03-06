/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:47:52 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:47:54 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_queue(t_shell *shell, char *command)
{
	int		i;
	char	**splited_cmd;
	int		number_of_element;
	t_cmd	*cmd;

	splited_cmd = ft_split_clean(shell, command, '|');
	number_of_element = get_size(splited_cmd);
	shell->queue = ft_safe_malloc(sizeof(t_built) * number_of_element, shell);
	i = 0;
	while (i < number_of_element)
	{
		cmd = ft_safe_malloc(sizeof(t_cmd), shell);
		cmd->id = i;
		cmd->full_cmd = splited_cmd[i];
		shell->queue[i] = cmd;
		i++;
	}
}

void	init_env_lst(t_shell *shell, char **envp)
{
	int		i;
	char	**split;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		split = ft_split_clean(shell, envp[i], '=');
		key = split[0];
		value = split[1];
		ft_create_var(key, value, shell);
		i++;
	}
}

void	init_env(t_shell *shell, char **envp)
{
	static int	shlvl;

	init_env_lst(shell, envp);
	shlvl = ft_atoi(get_env_object("SHLVL", shell)->value);
	ft_create_var("SHLVL", ft_itoa_clean(shell, shlvl + 1), shell);
}
