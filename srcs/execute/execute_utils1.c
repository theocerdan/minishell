/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:18:40 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:18:41 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_built	g_built[] = {
{CD, "cd", &ft_cd},
{ENV, "env", &ft_env},
{PWD, "pwd", &ft_pwd},
{EXPORT, "export", &ft_export},
{UNSET, "unset", &ft_unset},
{EXIT, "exit", &ft_exit},
{ECHO, "echo", &ft_echo},
{EXEC, "exec", NULL}
};

int	str_equals_ignore_case(char *text_1, char *text_2)
{
	int	e;

	e = 0;
	if (ft_strlen(text_1) == 0 || ft_strlen(text_2) == 0)
		return (0);
	if (ft_strlen(text_1) != ft_strlen(text_2))
		return (0);
	while ((e < (int)ft_strlen(text_1))
		&& (ft_tolower(text_1[e]) == ft_tolower(text_2[e])))
			e++;
	if (ft_strlen(text_1) == (size_t)e)
		return (1);
	return (0);
}

t_built	get_command_type(char *cmd)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (str_equals_ignore_case(g_built[i].cmd, cmd))
			return (g_built[i]);
		i++;
	}
	return (g_built[7]);
}

char	*get_executable(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str && str[i] != ' ' && str[i] != '\0')
		i++;
	tmp = ft_substr(str, 0, i);
	return (tmp);
}
