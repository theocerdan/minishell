/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:48:45 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 13:48:47 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	non_digit_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	exit_value(t_shell *shell, int ret, char *each_cmd)
{
	int		count;

	count = count_spacing(shell, ' ', shell->command_line_clean);
	ret = ft_atoi(shell->command_line_clean + ft_strlen(each_cmd) + 1) % 256;
	if (count > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	else if (count > 1 && non_digit_arg(shell->command_line_clean
			+ ft_strlen(each_cmd) + 1))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			shell->command_line_clean + ft_strlen(each_cmd) + 1);
		exit (1);
	}
	else
	{
		write(2, "exit\n", 5);
		exit(ret);
	}
}

void	ft_exit(t_shell *shell, char *each_cmd)
{
	exit_value(shell, 0, each_cmd);
}
