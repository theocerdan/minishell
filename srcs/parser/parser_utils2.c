/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:21:19 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/23 17:21:20 by mbaurin          ###   ########lyon.fr   */
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

int	extra_space(t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	while (shell->command_line_clean[i++] != ' ')
		if (shell->command_line_clean[i] == '\0')
			return (0);
	count = 1;
	if (shell->command_line_clean[i] == ' ')
		while (shell->command_line_clean[i++] == ' ')
			count++;
	if (count >= 2)
		return (1);
	return (0);
}

int	start_space(t_shell *shell)
{
	if (shell->command_line_clean[0] == ' ')
		return (1);
	return (0);
}

int	is_index_is_between_quote(int index, t_shell *shell)
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
		if (is_quote(shell->command_line_clean[i]))
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

void	operate_start_space(t_shell *shell)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (shell->command_line_clean[i] == ' ')
		i++;
	count = i;
	j = 0;
	while (shell->command_line_clean[count])
	{
		count++;
		j++;
	}
	shell->command_line_clean = ft_substr_clean(shell,
			shell->command_line_clean, i, j);
}
