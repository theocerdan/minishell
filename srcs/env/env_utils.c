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

char** convert_env_to_string_tab(t_shell *shell){
	t_list	*lst;
	t_env	*env;
	char 	**ret_tab;
	int 	i;
	int		s_len;

	s_len = 0;
	i = 0;
	ret_tab = ft_safe_malloc(env_len(shell) * sizeof(char*), shell);
	lst = shell->env_vars;
	if (!lst)
		return (NULL);
	while (lst)
	{
		env = (t_env *)lst->content;
		s_len = 1 + ft_strlen(env->key) + ft_strlen(env->value);
		ret_tab[i] = ft_strjoin(env->key, "=");
		ret_tab[i] = ft_strjoin(ret_tab[i], env->value);
		lst = lst->next;
		i++;
	}
	return (ret_tab);
}