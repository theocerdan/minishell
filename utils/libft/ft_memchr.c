/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <mbaurin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:36:04 by mbaurin           #+#    #+#             */
/*   Updated: 2020/11/23 11:36:53 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str1;
	size_t	i;

	str1 = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)str1[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
