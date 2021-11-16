/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_cleaner2000.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:47:39 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:47:40 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clean(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_add_to_garbage(void *ptr, t_shell *s)
{
	ft_lstadd_front(&(s->ptrs), ft_lstnew(ptr));
}

void	ft_total_clean(t_shell *m)
{
	ft_lstclear(&(m->ptrs), &ft_clean);
	ft_clean(m->ptrs);
	ft_clean(m);
}

void	*ft_safe_malloc(unsigned int size, t_shell *s)
{
	void	*ptr;

	ptr = (char *)malloc(size);
	if (!ptr)
	{
		printf("Malloc error\n");
		exit(0);
		return (NULL);
	}
	if (s != NULL)
		ft_add_to_garbage(ptr, s);
	return (ptr);
}
