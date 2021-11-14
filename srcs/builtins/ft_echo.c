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
	int		n_flag;

	n_flag = 0;
	if (each_cmd[5] == '-' && each_cmd[6] == 'n')
		n_flag = 1;
	return (n_flag);
}

void	ft_echo(t_shell *shell, char *cmd)
{
	int		n_flag;
	int		i;

	(void)(cmd);
	if (ft_strcmp(shell->command_line_clean, "echo") == 0)
	{
		printf("\n");
		return ;
	}
	n_flag = get_flag(shell->command_line_clean);
	if (n_flag)
		i = 8;
	else
		i = 5;
	while (shell->command_line_clean[i])
		printf("%c", shell->command_line_clean[i++]);
	if (n_flag == 0)
		printf("\n");
}
