/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_key_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:50:32 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/23 17:50:33 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_index_is_between_single_quote(int index, t_shell *shell)
{
	int		inside;
	int		f_i;
	int		i;
	int		a;

	inside = 0;
	f_i = 0;
	a = 0;
	i = -1;
	while (++i < (int)ft_strlen(shell->command_line_clean))
	{
		if (shell->command_line_clean[i] == '\'')
		{
			inside = !inside;
			if (inside)
				f_i = i;
			if (index > f_i && index < (f_i + a))
				return (1);
		}
		if (inside)
			a++;
		else
			a = 0;
	}
	return (0);
}

int	env_between_simple_quotes(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$' && next_word_env_key(shell))
			return (is_index_is_between_single_quote(i, shell));
		i++;
	}
	return (0);
}

int	dollar_plus_number(t_shell *shell)
{
	int	i;

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

int	key_plus_numbers(t_shell *shell)
{
	int	i;

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
				else if (shell->command_line_clean[i + 1] == ' '
					|| ft_is_lowercase(shell->command_line_clean[i + 1])
					|| shell->command_line_clean[i + 1] == '\0'
					|| ft_is_special(shell->command_line_clean[i + 1]))
					return (0);
				i++;
			}
		}
		i++;
	}
	return (0);
}
