/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:48:07 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 13:48:09 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_flag(char *each_cmd)
{
	int	n_flag;

	n_flag = 0;
	if (each_cmd[5] == '-' && each_cmd[6] == 'n')
		n_flag = 1;
	return (n_flag);
}

static int	get_i(t_shell *shell, int i)
{
	while (shell->command_line_clean[i] == '-'
		|| shell->command_line_clean[i] == 'n'
		|| shell->command_line_clean[i] == ' ')
			i++;
	return (i);
}

void	ft_echo(t_shell *shell, char *cmd)
{
	int	n_flag;
	int	i;

	shell->error_return = 0;
	(void)(cmd);
	if (ft_strlen(shell->command_line_clean) == 4)
		shell->command_line_clean = lower_str(shell->command_line_clean);
	if (ft_strcmp(shell->command_line_clean, "echo") == 0)
	{
		printf("\n");
		return ;
	}
	n_flag = get_flag(shell->command_line_clean);
	i = 5;
	if (n_flag)
	{
		i++;
		i = get_i(shell, i);
	}
	while (shell->command_line_clean[i])
		printf("%c", shell->command_line_clean[i++]);
	if (n_flag == 0)
		printf("\n");
}
