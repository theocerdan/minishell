/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:49:05 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 13:49:06 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_swap_env(t_env *a, t_env *b)
{
	char *tmp;
	int visible;

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

void ft_sort_export_env(t_list *new)
{
	t_list *lst;
	t_env *env;
	t_env *next_env;

	lst = new;
	while (lst && lst->next)
	{
		env = (t_env *)lst->content;
		next_env = (t_env *)lst->next->content;
		if (ft_strcmp(env->key, next_env->key) > 0)
		{
			ft_swap_env(env, next_env);
			lst = new;
		}
		else
			lst = lst->next;
	}
}

t_list *clone_env(t_shell *shell)
{
	t_list *lst;
	t_list *new_lst;
	t_env *new;
	t_env *old;

	new_lst = NULL;
	lst = shell->env_vars;
	while (lst && lst->next)
	{
		old = (t_env *)lst->content;
		new = ft_safe_malloc(sizeof(t_env), shell);
		new->key = old->key;
		new->value = old->value;
		new->visible = old->visible;
		ft_lstadd_front(&(new_lst), ft_lstnew(new));
		lst = lst->next;
	}
	return (new_lst);
}

static int get_i(char *first_arg)
{
	int i;

	i = 0;
	while (first_arg[i])
	{
		if (first_arg[i] == '=')
			break;
		i++;
	}
	return (i);
}

int not_acceptable(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_is_special(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void ft_export(t_shell *shell, char *each_cmd)
{
	t_env *env;
	t_list *new;
	char *first_arg;
	int i;

	(void)(each_cmd);
	first_arg = get_first_arg(shell->command_line_clean);
	env = NULL;
	if (ft_strlen(first_arg) > 0)
	{
		i = get_i(first_arg);
		env = ft_safe_malloc(sizeof(t_env), shell);
		env->key = ft_substr(first_arg, 0, i);
		env->value = ft_substr(first_arg, i + 1,
							   ft_strlen(first_arg) - ft_strlen(env->key));
		env->visible = 1;
		if (ft_strcmp(env->value, "") == 0)
			return;
		if (not_acceptable(env->key))
		{
			printf("minishell: export: not valid in this context: %s\n", env->key);
			return;
		}
		ft_lstadd_front(&(shell->env_vars), ft_lstnew(env));
	}
	else
	{
		new = clone_env(shell);
		ft_sort_export_env(new);
		print_all_env(new);
	}
}
