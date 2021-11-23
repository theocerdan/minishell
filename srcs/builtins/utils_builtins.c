/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:04:31 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:04:32 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_argc(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

char	*get_first_arg(t_shell *shell, char *each_cmd)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 0;
	while (each_cmd[i])
	{
		if (each_cmd[i] == ' ')
			break ;
		i++;
	}
	i++;
	res = NULL;
	tmp = ft_substr_clean(shell, each_cmd, i, ft_strlen(each_cmd) - i);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == ' ')
		{
			res = ft_substr_clean(shell, tmp, 0, i);
			break ;
		}
		i++;
	}
	return (tmp);
}

char	*get_first_word_cmd(t_shell *shell, char *each_cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (each_cmd[i])
	{
		if (each_cmd[i] == ' ')
			break ;
		i++;
	}
	tmp = ft_substr_clean(shell, each_cmd, 0, i);
	return (tmp);
}

int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && (s[i] == '\t' || s[i] == '\f' || s[i] == '\r'))
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	i = 0;
	while (*s == '-' || *s == '+' || *s == '0')
		s++;
	while (s[i])
		i++;
	if (i > 19)
		return (0);
	return (1);
}
