/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaguellette.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:34:14 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:34:16 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	have_vaguellette(t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
	str = shell->command_line_clean;
	while (str[i])
	{
		if (str[i] == '~' && !is_quote(str[i - 1])
			&& !is_quote(str[i + 1]) && !ft_isdigit(str[i - 1])
			&& !ft_isdigit(str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_home(t_shell *shell)
{
	t_list	*lst;
	t_env	*env;

	lst = shell->env_vars;
	while (lst)
	{
		env = (t_env *)lst->content;
		if (ft_strcmp(env->key, "HOME") == 0)
			return (env->value);
		lst = lst->next;
	}
	return (NULL);
}

char	*treat_each_vaguellette(t_shell *shell)
{
	int		lenght_rest;
	int		pos;
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while (shell->command_line_clean[i] != '~')
		i++;
	tmp1 = ft_strjoin_clean(shell, ft_substr_clean(shell,
				shell->command_line_clean, 0, i), get_home(shell));
	i++;
	pos = i;
	lenght_rest = 0;
	while (shell->command_line_clean[i++])
		lenght_rest++;
	tmp2 = ft_substr_clean(shell, shell->command_line_clean, pos, lenght_rest);
	return (ft_strjoin_clean(shell, tmp1, tmp2));
}

void	resolve_vaguellette(t_shell *shell)
{
	int	b;

	b = 1;
	while (b)
	{
		shell->command_line_clean = treat_each_vaguellette(shell);
		b = have_vaguellette(shell);
	}
}
