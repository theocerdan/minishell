/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:40:12 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:40:14 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *check_and_insert_spaces(char *cmd, t_shell *shell)
{
	char *current;
	char *tmp;
	char *result;
	int i;

	i = 0;
	current = cmd;
	tmp = cmd;
	result = " ";
	while (current != NULL && current[i])
	{
		if (i > 0 && no_blanks_around_operator(current[i],
											   current[i + 1], current[i - 1]))
		{
			result = " ";
			tmp = insert_spaces(cmd, current[i], i, shell);
			result = ft_strjoin_clean(shell, result, tmp);
		}
		else
			result = tmp;
		i++;
	}
	return (result);
}

int toujours_mal_formate(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|' && !(is_between_blanks(cmd[i + 1], cmd[i - 1])))
			return (1);
		i++;
	}
	return (0);
}

char *resolve_space_issue(char *cmd, t_shell *shell)
{
	char *result;
	int b;

	b = 1;
	result = cmd;
	while (b)
	{
		result = check_and_insert_spaces(result, shell);
		b = toujours_mal_formate(result);
	}
	return (result);
}

int tokenization(t_shell *shell, char *cmd)
{
	if (no_need_to_tokenization(cmd)){
		shell->command_line_clean = NULL;
		return 0;
	} 
	cmd = resolve_space_issue(cmd, shell);
	shell->command_line_clean = cmd;
	init_token(shell, cmd);
	return 1;
}
