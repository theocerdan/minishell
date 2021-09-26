/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <mbaurin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:18:47 by mbaurin           #+#    #+#             */
/*   Updated: 2020/11/26 13:20:58 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*old_elem;

	if (!del)
		return ;
	while (*lst)
	{
		old_elem = *lst;
		del(old_elem->content);
		*lst = old_elem->next;
		free(old_elem);
	}
	*lst = NULL;
}
