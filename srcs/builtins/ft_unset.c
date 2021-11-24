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

int	first_arg_not_key(t_shell *shell, char *str)
{
	t_list	*lst;
	t_env	*env;

	lst = shell->env_vars;
	if (!lst)
		return (0);
	while (lst)
	{
		env = (t_env *)lst->content;
		if (ft_strcmp(env->key, str) == 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	first_arg_ignore(char *str)
{
	int	i;
	int	count_maj;
	int	spe_char;

	i = 0;
	count_maj = 0;
	spe_char = 0;
	if (ft_strcmp(str, "0") == 0)
		return (0);
	while (str[i])
	{
		if (ft_is_uppercase(str[i]) || ft_is_lowercase(str[i]))
			count_maj++;
		else if (ft_is_special(str[i]))
			spe_char++;
		i++;
	}
	if (count_maj == (int)ft_strlen(str))
		return (0);
	else if (spe_char)
		return (1);
	return (0);
}

void	delete_env_value(t_shell *shell, char **args, int i)
{
	while (args[i])
	{
		ft_delete_var(args[i], shell);
		i++;
	}
}

void	ft_unset(t_shell *shell, char *each_cmd)
{
	char	*first_arg;
	char	**args;
	int		i;

	(void)(each_cmd);
	i = 1;
	shell->error_return = 0;
	args = ft_split_clean(shell, shell->command_line_clean, ' ');
	if ((int)ft_strlen(args[i]) == 0)
	{
		shell->error_return = 1;
		printf("minishell: unset: not enough arguments\n");
		return ;
	}
	if (first_arg_ignore(args[i]))
		return ;
	else if (first_arg_not_key(shell, args[i]))
	{
		shell->error_return = 1;
		printf("minishell: unset: %s: invalid parameter name\n", args[i]);
		return ;
	}
	else if (ft_strlen(first_arg) > 0)
		delete_env_value(shell, args, i);
}
