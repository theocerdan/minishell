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

void	exit_value(t_shell *shell, int ret, char *each_cmd)
{
	int	error;

	error = 0;
	ret = ft_atoi(each_cmd);
	if (ret > 255)
	{
		ft_total_clean(shell);
		exit(ret - 1 - 255);
	}
	else if (ret < 0)
	{
		ft_total_clean(shell);
		exit(256 + ret);
	}
	else
		exit(ret);
}

void	ft_exit(t_shell *shell, char *each_cmd)
{
	char	*first_arg;

	write(2, "exit\n", 5);
	first_arg = get_first_arg(each_cmd);
	if (!first_arg)
	{
		ft_total_clean(shell);
		exit(shell->error_return);
	}
	if (!ft_isnumber(first_arg))
	{
		printf("minishell: exit: %s : numeric argument required\n", first_arg);
		ft_total_clean(shell);
		exit(255);
	}
	if (get_argc(each_cmd) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		ft_total_clean(shell);
		exit(1);
	}
	exit_value(shell, 0, each_cmd);
}
