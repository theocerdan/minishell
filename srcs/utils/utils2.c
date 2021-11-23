/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:09:20 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/23 15:09:21 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	count_spacing(t_shell *shell, char c, char *text)
{
	char	**malaga;
	int		i;

	i = 0;
	malaga = ft_split_clean(shell, text, c);
	while (malaga[i])
		i++;
	return (i);
}
