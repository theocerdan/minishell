/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <mbaurin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:36:04 by mbaurin           #+#    #+#             */
/*   Updated: 2020/12/07 10:58:05 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void			conversion(char *str, long nbr, unsigned int nbrdigit,
	int sign)
{
	str[nbrdigit] = '\0';
	nbrdigit = nbrdigit - 1;
	str[nbrdigit] = nbr % 10 + '0';
	nbr = nbr / 10;
	while (nbr > 0)
	{
		nbrdigit = nbrdigit - 1;
		str[nbrdigit] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (sign == -1)
		str[0] = '-';
}

static unsigned int	getdigit(long nbr, int sign)
{
	unsigned int	nbrdigit;

	if (nbr == 0)
		return (1);
	nbrdigit = 0;
	while (nbr > 0)
	{
		nbr = nbr / 10;
		nbrdigit++;
	}
	if (sign == -1)
		nbrdigit++;
	return (nbrdigit);
}

char				*ft_itoa(int n)
{
	char			*str;
	unsigned int	nbr;
	int				sign;
	unsigned int	nbrdigit;

	sign = 1;
	if (n < 0)
	{
		nbr = (unsigned int)n * -1;
		sign = -1;
	}
	else
		nbr = n;
	nbrdigit = getdigit(nbr, sign);
	if (!(str = malloc(sizeof(char) * (nbrdigit + 1))))
		return (NULL);
	conversion(str, nbr, nbrdigit, sign);
	return (str);
}
