/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:17:15 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:17:16 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(void *ptr)
{
	t_env	*env;

	env = (t_env *)ptr;
	if (env->visible == 1)
		printf("%s=%s\n", env->key, env->value);
}

void	print_all_env(t_list *lst)
{
	ft_lstiter((lst), &print_env);
}
