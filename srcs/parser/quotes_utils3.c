/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:29:58 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 16:30:00 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	get_to_remove_single_quote(char *str, int i)
{
	char	to_remove;

	to_remove = '\0';
	while (!is_quote(str[i + 1]))
		i++;
	i++;
	if (str[i] == '\"')
		to_remove = '\'';
	return (to_remove);
}

char	get_to_remove_double_quote(char *str, int i)
{
	char	to_remove;

	to_remove = '\0';
	while (!is_quote(str[i + 1]))
		i++;
	i++;
	if (str[i] == '\'')
		to_remove = '\"';
	return (to_remove);
}

char	get_to_remove(char *str, int i, char to_remove)
{
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] == '\"')
		{
			to_remove = '\'';
			break ;
		}
		else if (str[i] == '\"' && str[i + 1] == '\'')
		{
			to_remove = '\"';
			break ;
		}
		else if (str[i] == '\'' && !is_quote(str[i + 1]))
		{
			to_remove = get_to_remove_single_quote(str, i);
			break ;
		}
		else if (str[i] == '\"' && !is_quote(str[i + 1]))
		{
			to_remove = get_to_remove_double_quote(str, i);
			break ;
		}
		i++;
	}
	return (to_remove);
}

char	get_quote_to_remove(char *str)
{
	int		i;
	char	to_remove;

	i = 0;
	to_remove = 0;
	to_remove = get_to_remove(str, i, to_remove);
	return (to_remove);
}
