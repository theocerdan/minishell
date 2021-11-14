/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:29:02 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:29:04 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start_and_end_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
			i++;
	if (is_quote(str[0]))
		if (is_quote(str[i - 1]))
			return (1);
	return (0);
}

void	parse_command(t_shell *shell)
{
	int	*each_cmd_lenght;
	int	i;

	if (shell->command_line_clean == NULL)
		return ;
	if (have_vaguellette(shell))
		resolve_vaguellette(shell);
	if (have_env_variables(shell))
		resolve_replace_key_to_value_env(shell);
	shell->nbr_cmd = get_number_of_commands(shell);
	each_cmd_lenght = get_each_cmd_lenght(shell, shell->nbr_cmd);
	shell->tab_cmd = (char **)malloc((shell->nbr_cmd + 1) * sizeof(char *));
	fill_cmd_array(shell, each_cmd_lenght);
	i = 0;
	while (i < shell->nbr_cmd)
	{
		if (start_and_end_quotes(shell->tab_cmd[i]))
		{
			execute_cmd(shell, shell->tab_cmd[i]);
			return ;
		}
		i++;
	}
	shell->command_line_clean = check_if_quotes(shell->command_line_clean);
	execute(shell);
}

void	parser(t_shell *shell)
{
	shell->fd = 0;
	parse_command(shell);
	if (shell->fd != 0)
		close(shell->fd);
}
