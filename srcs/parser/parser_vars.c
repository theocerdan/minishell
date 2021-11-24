/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 23:45:46 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/23 23:45:48 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_all_key(t_shell *shell, int found, int start, int end)
{
	int	i;
	int	tmp_end;

	tmp_end = 0;
	i = 0;
	while (i <= (int)ft_strlen(shell->command_line_clean))
	{
		if (found)
		{
			if (!ft_isalnum(shell->command_line_clean[i])
				&& shell->command_line_clean[i] != '_')
			{
				end = i;
				found = false;
				replace(shell, start, end);
			}
		}
		tmp_end = replace_all_key_2(shell, i, &found, &start);
		if (tmp_end != -3)
			end = tmp_end;
		i++;
	}
}

int	replace_all_key_2(t_shell *shell, int i, int *found, int *start)
{
	int	end;

	end = -2;
	if (shell->command_line_clean[i] == '$'
		&& !is_index_is_between_single_quote(i, shell))
	{
		if (shell->command_line_clean[i + 1] == '?')
			replace2(shell, i, i + 2);
		else
		{
			*found = 1;
			*start = i;
			end = -1;
		}
	}
	return (end);
}

int	replace(t_shell *shell, int start, int end)
{
	char				*phrase;
	char				*oldw;
	char				*key;
	char				*neww;
	t_replace_struct	*replace;

	phrase = shell->command_line_clean;
	oldw = ft_substr_clean(shell, phrase, start, end - start);
	key = oldw + 1;
	neww = ft_strdup_clean(shell, "");
	if (env_key_exist(key, shell))
		neww = get_env_object(key, shell)->value;
	replace = ft_safe_malloc(sizeof(t_replace_struct), shell);
	replace->phrase = phrase;
	replace->oldw = oldw;
	replace->neww = neww;
	replace->nlen = (int)ft_strlen(neww);
	replace->olen = (int)ft_strlen(oldw);
	replace->cnt = 0;
	replace->i = 0;
	shell->command_line_clean = replaceword(replace, shell);
	shell->command_line_clean[replace->i] = '\0';
	return (1);
}

int	replace2(t_shell *shell, int start, int end)
{
	char				*phrase;
	char				*oldw;
	char				*key;
	char				*neww;
	t_replace_struct	*replace;

	phrase = shell->command_line_clean;
	oldw = ft_substr_clean(shell, phrase, start, end - start);
	key = oldw + 1;
	neww = ft_strdup_clean(shell, ft_itoa_clean(shell, shell->error_return));
	replace = ft_safe_malloc(sizeof(t_replace_struct), shell);
	replace->phrase = phrase;
	replace->oldw = oldw;
	replace->neww = neww;
	replace->nlen = (int)ft_strlen(neww);
	replace->olen = (int)ft_strlen(oldw);
	replace->cnt = 0;
	replace->i = 0;
	shell->command_line_clean = replaceword(replace, shell);
	shell->command_line_clean[replace->i] = '\0';
	return (1);
}

char	*replaceword(t_replace_struct *r, t_shell *shell)
{
	char	*re;

	while (r->phrase[r->i])
	{
		if (strstr(&r->phrase[r->i], r->oldw) == &r->phrase[r->i])
			r->i += r->olen - 1;
		r->i++;
	}
	r->cnt = 1;
	re = (char *)ft_safe_malloc(r->i + r->cnt * (r->nlen - r->olen) + 1, shell);
	r->i = 0;
	while (*r->phrase)
	{
		if (r->cnt && strstr(r->phrase, r->oldw) == r->phrase
			&& !is_index_is_between_single_quote(r->i, shell))
		{
			strcpy(&re[r->i], r->neww);
			r->i += r->nlen;
			r->phrase += r->olen;
			r->cnt = 0;
		}
		else
			re[r->i++] = *r->phrase++;
	}
	return (re);
}
