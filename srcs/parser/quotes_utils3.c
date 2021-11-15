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

char	get_quote_to_remove(char *str)
{
	int		i;
	char	to_remove;

	i = 0;
	to_remove = 0;
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
		else if (str[i] == '\'' && str[i + 1] == ' ')
		{
			while (str[i + 1] == ' ')
				i++;
			i++;
			if (str[i] == '\"')
			{
				to_remove = '\'';
				break ;
			}
		}
		else if (str[i] == '\"' && str[i + 1] == ' ')
		{
			while (str[i + 1] == ' ')
				i++;
			i++;
			if (str[i] == '\'')
			{
				to_remove = '\"';
				break ;
			}
		}
		i++;
	}
	return (to_remove);
}
