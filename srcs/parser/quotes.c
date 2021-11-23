/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:30:58 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:30:59 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int has_two_type_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			if (str[i] == '\"')
				return (1);
			else if (!is_quote(str[i]))
			{
				while (!is_quote(str[i]))
					i++;
				if (str[i] == '\"')
					return (1);
			}
			else
				return (0);
		}
		if (str[i] == '\"')
		{
			i++;
			if (str[i] == '\'')
				return (1);
			else if (!is_quote(str[i]))
			{
				while (!is_quote(str[i]))
					i++;
				if (str[i] == '\'')
					return (1);
			}
			else
				return (0);
		}
		i++;
	}
	return (0);
}

char *resolve_quote_issue(t_shell *shell, char *str)
{
	char *result;
	int b;

	b = 1;
	result = str;
	while (b)
	{
		result = operate_quotes(shell, result);
		b = still_has_quote(result);
	}
	return (result);
}

int only_one_type_of_quotes_remaining(char *str)
{
	int i;
	int sql_qts;
	int dbl_qts;

	i = 0;
	sql_qts = 0;
	dbl_qts = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sql_qts++;
		else if (str[i] == '\"')
			dbl_qts++;
		i++;
	}
	if (sql_qts == 0 && dbl_qts != 0)
		return (1);
	else if (sql_qts != 0 && dbl_qts == 0)
		return (1);
	return (0);
}

char *resolve_special_case_quotes(t_shell *shell, char *str)
{
	char *result;
	int b;

	result = str;
	b = 1;
	while (b)
	{
		result = special_case_quotes(shell, result);
		b = has_two_type_quotes(result);
	}
	return (result);
}

int	empty_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && str[i + 1] == '\"')
			return (1);
		if (str[i] == '\'' && str[i + 1] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*cut_empty_quotes(t_shell *shell, char *str)
{
	int		i;
	int		start;
	int		lenght;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	start = 0;
	lenght = 0;
	while (str[i])
	{
		if  ((str[i] == '\"' && str[i + 1] == '\"') || (str[i] == '\'' && str[i + 1] == '\''))
		{
			start = i;
			while (str[i])
			{
				lenght++;
				i++;
			}
			break ;
		}
		i++;
	}
	tmp1 = ft_substr_clean(shell, str, 0, start);
	tmp2 = ft_substr_clean(shell, str, start + 2, lenght);
	return (ft_strjoin_clean(shell, tmp1, tmp2));
}

char	*resolve_cut_empty_quotes(t_shell *shell, char *str)
{
	char *result;
	int b;

	result = str;
	b = 1;
	while (b)
	{
		result = cut_empty_quotes(shell, result);
		b = empty_quotes(result);
	}
	return (result);
}

char *check_if_quotes(t_shell *shell, char *each_cmd)
{
	int i;
	char *str;

	i = 0;
	str = each_cmd;
	while (str[i])
	{
		if (quote_hole(str, str[i]))
		{
			printf("Error : need a quote to finish the line.\n");
			exit(0);
		}
		else if (empty_quotes(str))
			str = resolve_cut_empty_quotes(shell, str);
		else if (has_two_type_quotes(str))
		{
			str = resolve_special_case_quotes(shell, str);
			break;
		}
		else if (is_between_quotes(str, i, str[i]))
			str = resolve_quote_issue(shell, str);
		i++;
	}
	return (str);
}
