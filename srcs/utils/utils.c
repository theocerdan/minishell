/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:50:39 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:50:40 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	get_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	ft_is_uppercase(char c)
{
	if (c >= 65 && c <= 90)
		return (1);
	return (0);
}

char	*lower_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_uppercase(str[i]))
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}
