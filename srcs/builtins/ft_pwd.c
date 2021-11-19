/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:04:01 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:04:02 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_pwd(t_shell *shell, char *cmd)
{
	char *cwd;
	char *buffer;

	(void)(shell);
	(void)(cmd);
	buffer = NULL;
	cwd = getcwd(buffer, 0);
	if (cwd)
		printf("%s\n", cwd);
	else
		ft_error("minishell: error pwd\n");
	ft_add_to_garbage(cwd, shell);
}
