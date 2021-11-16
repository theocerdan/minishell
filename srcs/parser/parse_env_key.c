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

char	*get_tmp2(t_shell *shell)
{
	char	*to_replace;
	char	*tmp1;
	int		i;

	to_replace = get_replacement_env_key(shell);
	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
			break ;
		i++;
	}
	tmp1 = ft_substr(shell->command_line_clean, 0, i);
	return (ft_strjoin(tmp1, to_replace));
}

char	*replace_key_to_value_env(t_shell *shell)
{
	int		i;
	int		pos;
	int		lenght_rest;
	char	*tmp2;
	char	*tmp3;

	tmp2 = get_tmp2(shell);
	i = 0;
	while (shell->command_line_clean[i])
	{
		if (ft_is_uppercase(shell->command_line_clean[i])
			&& !ft_is_uppercase(shell->command_line_clean[i + 1]))
			break ;
		i++;
	}
	pos = i + 1;
	lenght_rest = 0;
	while (shell->command_line_clean[i++])
		lenght_rest++;
	tmp3 = ft_substr(shell->command_line_clean, pos, lenght_rest);
	return (ft_strjoin(tmp2, tmp3));
}

void	resolve_replace_key_to_value_env(t_shell *shell)
{
	int		b;

	b = 1;
	while (b)
	{
		shell->command_line_clean = replace_key_to_value_env(shell);
		b = have_env_variables(shell);
	}
}
