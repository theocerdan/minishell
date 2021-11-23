/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:13:39 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/23 15:13:41 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	not_acceptable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_special(str[i]) && str[i] != '_'  && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	first_arg_finish_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '=')
		return (1);
	return (0);
}

void	ft_swap_env(t_env *a, t_env *b)
{
	char	*tmp;
	int		visible;

	tmp = a->key;
	a->key = b->key;
	b->key = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
	visible = a->visible;
	a->visible = b->visible;
	b->visible = visible;
}

void	continue_export_value(t_shell *shell, t_env *env)
{
	if (env_key_exist(env->key, shell))
		get_env_object(env->key, shell)->value = env->value;
	else
		ft_lstadd_front(&(shell->env_vars), ft_lstnew(env));
}

t_env	*init_env_buitins(t_shell *shell, int i, t_env *env, char *first_arg)
{
	env = ft_safe_malloc(sizeof(t_env), shell);
	env->key = ft_substr_clean(shell, first_arg, 0, i);
	env->value = ft_substr_clean(shell, first_arg, i + 1,
			ft_strlen(first_arg) - ft_strlen(env->key));
	env->visible = 1;
	return (env);
}
