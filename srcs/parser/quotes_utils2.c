/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:33:50 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:33:51 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_i(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			break ;
		i++;
	}
	return (i);
}

char	*operate_quotes(t_shell *shell, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		pos;
	int		j;
	int		i;

	i = get_i(str);
	pos = i;
	i = pos + 1;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && (str[i + 1] == '\0'))
			break ;
		j++;
		i++;
	}
	tmp1 = ft_substr_clean(shell, str, 0, pos);
	tmp2 = ft_substr_clean(shell, str, pos + 1, j);
	return (ft_strjoin_clean(shell, tmp1, tmp2));
}

char	*get_tmp_zero(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == get_quote_to_remove(str))
			break ;
		i++;
	}
	return (ft_substr_clean(shell, str, 0, i));
}

int	get_first_i(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == get_quote_to_remove(str))
			break ;
		i++;
	}
	return (i);
}

char	*special_case_quotes(t_shell *shell, char *str)
{
	int		lenght_rest;
	int		pos;
	int		i;
	int		j;
	char	*tmp[2];

	tmp[0] = get_tmp_zero(shell, str);
	i = get_first_i(str);
	i++;
	pos = i;
	j = 0;
	while (str[i])
	{
		if (str[i] == get_quote_to_remove(str) && !is_quote(str[i + 1]))
			break ;
		i++;
		j++;
	}
	tmp[1] = ft_substr_clean(shell, str, pos, j);
	pos = i + 1;
	lenght_rest = 0;
	while (str[i++])
		lenght_rest++;
	return (ft_strjoin_clean(shell, ft_strjoin_clean(shell, tmp[0], tmp[1]),
			ft_substr_clean(shell, str, pos, lenght_rest)));
}
