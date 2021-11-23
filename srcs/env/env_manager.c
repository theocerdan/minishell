/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:05:34 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:05:38 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env_object(char *target_key, t_shell *shell)
{
	t_list	*lst;
	t_env	*env;

	lst = shell->env_vars;
	if (!lst)
		return (NULL);
	while (lst)
	{
		env = (t_env *)lst->content;
		if (env->visible == 1 && ft_strcmp(env->key, target_key) == 0)
			return (env);
		lst = lst->next;
	}
	return (NULL);
}

int	env_value_exist(char *target_key, t_shell *shell)
{
	t_list	*lst;
	t_env	*env;

	lst = shell->env_vars;
	if (!lst)
		return (0);
	while (lst)
	{
		env = (t_env *)lst->content;
		if (env->visible == 1 && ft_strcmp(env->value, target_key) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	env_key_exist(char *target_key, t_shell *shell)
{
	t_list	*lst;
	t_env	*env;

	lst = shell->env_vars;
	if (!lst)
		return (0);
	while (lst)
	{
		env = (t_env *)lst->content;
		if (env->visible == 1 && ft_strcmp(env->key, target_key) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	ft_delete_var(char *target_key, t_shell *shell)
{
	t_list	*lst;
	t_env	*env;

	lst = shell->env_vars;
	if (!lst)
		return ;
	while (lst)
	{
		env = (t_env *)lst->content;
		if (ft_strcmp(env->key, target_key) == 0)
		{
			env->visible = 0;
			env->value = NULL;
		}
		lst = lst->next;
	}
}

void	ft_create_var(char *key, char *value, t_shell *shell)
{
	t_env	*env;

	env = get_env_object(key, shell);
	if (env != NULL)
	{
		env->value = value;
		env->visible = 1;
		return ;
	}
	env = ft_safe_malloc(sizeof(t_env), shell);
	env->key = key;
	env->value = value;
	env->visible = 1;
	ft_lstadd_front(&(shell->env_vars), ft_lstnew(env));
}
