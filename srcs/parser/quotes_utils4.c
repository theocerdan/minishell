/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:06:52 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/23 16:06:53 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	empty_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && str[i + 1] == '\"')
			return (1);
		if (str[i] == '\'' && str[i + 1] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	only_one_type_of_quotes_remaining(char *str)
{
	int	i;
	int	sql_qts;
	int	dbl_qts;

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
	if (sql_qts == 0 && dbl_qts != 0)
		return (1);
	else if (sql_qts != 0 && dbl_qts == 0)
		return (1);
	return (0);
}

int	trait_single_quotes(char *str, int i)
{
	i++;
	if (str[i] == '\"')
		return (1);
	else if (!is_quote(str[i]))
	{
		while (!is_quote(str[i]))
			i++;
		if (str[i] == '\"')
			return (1);
	}
	return (0);
}

int	trait_double_quotes(char *str, int i)
{
	i++;
	if (str[i] == '\'')
		return (1);
	else if (!is_quote(str[i]))
	{
		while (!is_quote(str[i]))
			i++;
		if (str[i] == '\'')
			return (1);
	}
	return (0);
}

int	has_two_type_quotes(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			ret = trait_single_quotes(str, i);
			return (ret);
		}
		if (str[i] == '\"')
		{
			ret = trait_double_quotes(str, i);
			return (ret);
		}
		i++;
	}
	return (0);
}
