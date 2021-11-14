/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <mbaurin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:36:04 by mbaurin           #+#    #+#             */
/*   Updated: 2020/11/23 11:36:53 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*c_in_s;

	if (c > 127)
		c %= 256;
	while (*s != '\0')
	{
		if (*s == c)
		{
			c_in_s = (char *)s;
			return (c_in_s);
		}
		s++;
	}
	if (*s == c)
	{
		c_in_s = (char *)s;
		return (c_in_s);
	}
	return (NULL);
}
