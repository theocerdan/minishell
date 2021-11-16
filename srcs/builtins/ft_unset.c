/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:04:15 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:04:16 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_shell *shell, char *each_cmd)
{
	char	*first_arg;

	first_arg = get_first_arg(each_cmd);
	if (ft_strlen(first_arg) > 0)
		ft_delete_var(first_arg, shell);
}
