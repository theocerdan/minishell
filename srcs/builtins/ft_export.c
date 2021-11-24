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

void	ft_sort_export_env(t_list *new)
{
	t_list	*lst;
	t_env	*env;
	t_env	*next_env;

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

static int	get_i(char *first_arg)
{
	int	i;
	int	res;

	i = 0;
	res = -1;
	while ((int)ft_strlen(first_arg) > i)
	{
		if (first_arg[i] == '=')
			res = i;
		i++;
	}
	return (res);
}

void	export_value(t_shell *shell, int i, t_env *env, char *first_arg)
{
	i = get_i(first_arg);
	env = init_env_buitins(shell, i, env, first_arg);
	if (ft_strcmp(env->key, "0") == 0)
	{
		env->value = "/bin/zsh";
		if (!env_key_exist(env->key, shell))
			ft_lstadd_front(&(shell->env_vars), ft_lstnew(env));
		return ;
	}
	if (i == -1 && ft_strlen(env->value) > 0)
		return ;
	if (not_acceptable(env->key))
	{
		printf("minishell: export: not valid in this context: %s\n",
			env->key);
		return ;
	}
	if (first_arg_finish_equal(first_arg))
	{
		if (!env_key_exist(env->key, shell))
			ft_lstadd_front(&(shell->env_vars), ft_lstnew(env));
		return ;
	}
	continue_export_value(shell, env);
}

void	export_export_value(t_shell *shell, t_env *env, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		export_value(shell, 0, env, args[i]);
		i++;
	}
}

void	ft_export(t_shell *shell, char *each_cmd)
{
	t_env	*env;
	t_list	*new;
	char	*first_arg;
	char	**args;
	int		i;

	(void)(each_cmd);
	i = 0;
	env = NULL;
	args = ft_split_clean(shell, shell->command_line_clean, ' ');
	first_arg = get_first_arg(shell, shell->command_line_clean);
	if (first_arg[0] == '=')
	{
		printf("minishell: export: not valid in this context: %s\n", first_arg);
		return ;
	}
	if (ft_strlen(first_arg) > 0)
		export_export_value(shell, env, args);
	else
	{
		new = clone_env(shell);
		ft_sort_export_env(new);
		print_all_env(new);
	}
}
