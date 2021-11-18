/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:23:43 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:23:44 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void prompt(t_shell *shell)
{
	char *cmd;
	int space_cmd;

	cmd = NULL;
	define_input_signals();
	while (1)
	{
		cmd = start_prompt(shell, cmd);
		add_history(cmd);
		//printf("cmd:%s|\n", cmd);
		space_cmd = tokenization(shell, cmd);
		if (space_cmd)
			parser(shell);
		ft_lstclear(&(shell->token_list), &free);
		//printf("clc:%s|\n", shell->command_line_clean);
		ft_add_to_garbage(cmd, shell);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell *shell;

	shell = NULL;
	shell = ft_safe_malloc(sizeof(t_shell), shell);
	shell->command_line_clean = NULL;
	shell->env_vars = NULL;
	shell->token_list = NULL;
	shell->error_return = 0;
	if (argc > 1 && argv)
		ft_error("too many arguments\n");
	init_env(shell, envp);
	prompt(shell);
	ft_total_clean(shell);
	return (0);
}
