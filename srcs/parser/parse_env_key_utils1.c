/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_key_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:28:31 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:28:32 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	have_env_variables(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->command_line_clean[i])
	{
		if (env_between_simple_quotes(shell))
			return (0);
		if (shell->command_line_clean[i] == '$' && next_word_env_key(shell))
			return (1);
		else if (shell->command_line_clean[i] == '$'
			&& shell->command_line_clean[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

int	get_count_to_split(t_shell *shell, int i)
{
	int	j;
	int	count;

	j = i + 1;
	count = 0;
	if (shell->command_line_clean[j] == '?')
		return (1);
	while (ft_is_uppercase(shell->command_line_clean[j])
		|| shell->command_line_clean[j] == '_')
	{
		count++;
		j++;
	}
	return (count);
}

char	*get_env_key(t_shell *shell)
{
	int		i;
	int		j;
	int		count;
	int		milestone;
	char	*tmp;

	i = 0;
	count = 0;
	milestone = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			j = i + 1;
			milestone = i + 1;
			count = get_count_to_split(shell, i);
			break ;
		}
		i++;
	}
	tmp = ft_substr_clean(shell, shell->command_line_clean, milestone, count);
	return (tmp);
}

int	next_word_env_key(t_shell *shell)
{
	char	*tmp;
	t_list	*lst;
	t_env	*env;

	tmp = get_env_key(shell);
	lst = shell->env_vars;
	while (lst)
	{
		env = (t_env *)lst->content;
		if (ft_strcmp(env->key, tmp) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

char	*get_replacement_env_key(t_shell *shell)
{
	char	*tmp;
	t_list	*lst;
	t_env	*env;

	tmp = get_env_key(shell);
	if (ft_strcmp(tmp, "?") == 0)
		return (ft_itoa_clean(shell, shell->error_return));
	lst = shell->env_vars;
	while (lst)
	{
		env = (t_env *)lst->content;
		if (ft_strcmp(env->key, tmp) == 0)
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}
