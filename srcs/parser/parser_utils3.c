/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:37:14 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/23 17:37:15 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_tmp2_dollar_plus_number(t_shell *shell)
{
	int		i;
	int		pos;
	int		flag;
	char	*tmp1;

	i = 0;
	pos = 0;
	flag = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			if (ft_isdigit(shell->command_line_clean[i + 1]))
			{
				pos = i;
				flag = 1;
			}
		}
		if (flag)
			break ;
		i++;
	}
	tmp1 = ft_substr_clean(shell, shell->command_line_clean, 0, pos);
	return (tmp1);
}

int	boucle_replace_dollar_plus_number(t_shell *shell, int i, int pos, int flag)
{
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			i++;
			if (ft_isdigit(shell->command_line_clean[i]))
			{
				while (shell->command_line_clean[i])
				{
					if (!ft_isdigit(shell->command_line_clean[i + 1]))
					{
						pos = i + 1;
						flag = 1;
						break ;
					}
					i++;
				}
			}
			if (flag)
				break ;
		}
		i++;
	}
	return (pos);
}

char	*replace_dollar_plus_number(t_shell *shell)
{
	int		i;
	int		pos;
	int		lenght_rest;
	char	*tmp2;
	char	*tmp3;

	tmp2 = get_tmp2_dollar_plus_number(shell);
	pos = boucle_replace_dollar_plus_number(shell, 0, 0, 0);
	i = pos;
	lenght_rest = 1;
	while (shell->command_line_clean[i++])
		lenght_rest++;
	tmp3 = ft_substr_clean(shell, shell->command_line_clean, pos, lenght_rest);
	return (ft_strjoin_clean(shell, tmp2, tmp3));
}
