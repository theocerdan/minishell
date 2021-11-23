/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:08:22 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/23 15:08:24 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_clean(t_shell *shell, const char *s1)
{
	char	*ret;

	ret = ft_strdup(s1);
	ft_add_to_garbage(ret, shell);
	return (ret);
}

char	*ft_strjoin_clean(t_shell *shell, const char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	ft_add_to_garbage(ret, shell);
	return (ret);
}

char	*ft_substr_clean(t_shell *shell, char const *s,
	unsigned int start, size_t len)
{
	char	*ret;

	ret = ft_substr(s, start, len);
	ft_add_to_garbage(ret, shell);
	return (ret);
}

char	**ft_split_clean(t_shell *shell, char const *s, char c)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_split(s, c);
	while (ret[i])
	{
		ft_add_to_garbage(ret[i], shell);
		i++;
	}
	ft_add_to_garbage(ret, shell);
	return (ret);
}
