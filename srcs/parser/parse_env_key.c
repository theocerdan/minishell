/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:24:52 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:24:53 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int dollar_plus_number(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
			if (ft_isdigit(shell->command_line_clean[i + 1]))
				return (1);
		i++;
	}
	return (0);
}

int key_plus_numbers(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			i++;
			while (ft_is_uppercase(shell->command_line_clean[i]))
			{
				if (ft_isdigit(shell->command_line_clean[i + 1]))
					return (1);
				else if (shell->command_line_clean[i + 1] == ' ' || ft_is_lowercase(shell->command_line_clean[i + 1]) || shell->command_line_clean[i + 1] == '\0' || ft_is_special(shell->command_line_clean[i + 1]))
					return (0);
				i++;
			}
		}
		i++;
	}
	return (0);
}

char *get_tmp2(t_shell *shell)
{
	char *to_replace;
	char *tmp1;
	int i;

	if (key_plus_numbers(shell))
		to_replace = "";
	else if (dollar_plus_number(shell))
		to_replace = "";
	else
		to_replace = get_replacement_env_key(shell);
	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
			break;
		i++;
	}
	tmp1 = ft_substr_clean(shell, shell->command_line_clean, 0, i);
	return (ft_strjoin_clean(shell, tmp1, to_replace));
}

int get_pos(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			i++;
			while (ft_is_uppercase(shell->command_line_clean[i]))
			{
				if (ft_isdigit(shell->command_line_clean[i + 1]))
				{
					i++;
					while (ft_isdigit(shell->command_line_clean[i]))
					{
						if (!ft_isdigit(shell->command_line_clean[i + 1]))
							return (i + 1);
						i++;
					}
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

char *replace_key_to_value_env(t_shell *shell)
{
	int i;
	int pos;
	int lenght_rest;
	char *tmp2;
	char *tmp3;
	int flag;

	tmp2 = get_tmp2(shell);
	i = 0;
	flag = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			i++;
			if (ft_is_uppercase(shell->command_line_clean[i]))
			{
				while (ft_is_uppercase(shell->command_line_clean[i]))
				{
					if (!ft_is_uppercase(shell->command_line_clean[i + 1]))
					{
						pos = i + 1;
						flag = 1;
						break;
					}
					i++;
				}
			}
			else if (shell->command_line_clean[i] == '?' && shell->command_line_clean[i - 1] == '$')
				pos = i + 1;
			if (flag)
				break;
		}
		i++;
	}
	i = pos;
	lenght_rest = 1;
	while (shell->command_line_clean[i++])
		lenght_rest++;
	if (key_plus_numbers(shell))
		pos = get_pos(shell);
	tmp3 = ft_substr_clean(shell, shell->command_line_clean, pos, lenght_rest);
	return (ft_strjoin_clean(shell, tmp2, tmp3));
}

void resolve_replace_key_to_value_env(t_shell *shell)
{
	int b;

	b = 1;
	while (b)
	{
		shell->command_line_clean = replace_key_to_value_env(shell);
		b = have_env_variables(shell);
	}
}
