/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:48:22 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 13:48:24 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_shell *shell, char *cmd)
{
	int arg_len;
	char **command;

	(void)cmd;
	shell->error_return = 0;
	arg_len = 0;
    command = ft_split_clean(shell, shell->command_line_clean, ' ');
    while (command[arg_len])
        arg_len++;
    if (arg_len > 1)
	{
		shell->error_return = 127;
		printf("env: %s: No such file or directory\n", command[1]);
	} else 
	{
		print_all_env(shell->env_vars);
	}
}
