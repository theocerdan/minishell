/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:45:59 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:46:00 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void free_aux_strings(char **left, char **operator,
					  char ** right, char **first_part, t_shell *shell)
{
	ft_add_to_garbage(left, shell);
	ft_add_to_garbage(operator, shell);
	ft_add_to_garbage(right, shell);
	ft_add_to_garbage(first_part, shell);
}

char *set_operator(t_shell *shell, char *line, char operator_pointer, int off_set)
{
	char *operator;

	operator=(char *)ft_safe_malloc(sizeof(char) * 3 + 1, shell);
	if (line[off_set + 1] == ' ')
	{
		operator[0] = ' ';
		operator[1] = operator_pointer;
		operator[2] = '\0';
	}
	else
	{
		operator[0] = ' ';
		operator[1] = operator_pointer;
		operator[2] = ' ';
		operator[3] = '\0';
	}
	return (operator);
}

char *insert_spaces(char *line, char operator_pointer, int off_set, t_shell *shell)
{
	char *left;
	char *operator;
	char *right;
	char *first_part;
	char *final_part;

	if (line[off_set - 1] == ' ')
		left = ft_substr_clean(shell, line, 0, off_set - 1);
	else
		left = ft_substr_clean(shell, line, 0, off_set);
	operator= set_operator(shell, line, operator_pointer, off_set);
	right = ft_substr_clean(shell, line, off_set + 1, ft_strlen(line));
	first_part = ft_strjoin_clean(shell, left, operator);
	final_part = ft_strjoin_clean(shell, first_part, right);
	free_aux_strings(&left, &operator, & right, &first_part, shell);
	return (final_part);
}
