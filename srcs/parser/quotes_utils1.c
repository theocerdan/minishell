/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:33:09 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:33:10 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	match(char *str, int i, char c)
{
	int	count;

	count = 0;
	while (str[i])
		if (str[i++] == c)
			count++;
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	is_between_quotes(char *str, int i, char c)
{
	if (is_quote(c) && match(str, i, c))
		return (1);
	return (0);
}

int	still_has_quote(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	quote_hole(char *str)
{
	int		i;
	int		sql_qts;
	int		dbl_qts;

	i = 0;
	sql_qts = 0;
	dbl_qts = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sql_qts++;
		else if (str[i] == '\"')
			dbl_qts++;
		i++;
	}
	if (sql_qts % 2 == 0 && dbl_qts % 2 == 0)
		return (0);
	return (1);
}
