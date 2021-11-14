/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:41:43 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:41:44 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *value)
{
	if (!value)
		return (0);
	if (get_command_type(value).id != EXEC)
		return (1);
	return (0);
}

int	is_double_quote(char *value)
{
	int	last_i;

	last_i = ft_strlen(value);
	if (!value)
		return (0);
	if (value[last_i - 1] == '"' && value[0] == '"')
		return (1);
	return (0);
}

int	is_single_quote(char *value)
{
	int	last_i;

	last_i = ft_strlen(value);
	if (!value)
		return (0);
	if (value[last_i - 1] == '\'' && value[0] == '\'')
		return (1);
	return (0);
}

int	is_operator(char *value)
{
	if (!(ft_strcmp(value, "|")) || !(ft_strcmp(value, ">"))
		|| !(ft_strcmp(value, "<")) || !(ft_strcmp(value, ">>"))
		|| !(ft_strcmp(value, "<<")))
		return (1);
	return (0);
}

int	is_env(char *value)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if ((value[i] >= 65 && value[i] <= 90) || value[i] == 36)
			i++;
		else
			return (0);
	}
	return (1);
}
