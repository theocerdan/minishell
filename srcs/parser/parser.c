/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:29:02 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:29:04 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int start_and_end_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (is_quote(str[0]))
		if (is_quote(str[i - 1]))
			return (1);
	return (0);
}

char *get_tmp2_dollar_plus_number(t_shell *shell)
{
	int i;
	int pos;
	int flag;
	char *tmp1;

	i = 0;
	pos = 0;
	flag = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			if (ft_isdigit(shell->command_line_clean[i + 1]))
			{
				pos = i;
				flag = 1;
			}
		}
		if (flag)
			break;
		i++;
	}
	tmp1 = ft_substr_clean(shell, shell->command_line_clean, 0, pos);
	return (tmp1);
}

char *replace_dollar_plus_number(t_shell *shell)
{
	int i;
	int pos;
	int flag;
	int lenght_rest;
	char *tmp2;
	char *tmp3;

	tmp2 = get_tmp2_dollar_plus_number(shell);
	i = 0;
	flag = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			i++;
			if (ft_isdigit(shell->command_line_clean[i]))
			{
				while (shell->command_line_clean[i])
				{
					if (!ft_isdigit(shell->command_line_clean[i + 1]))
					{
						pos = i + 1;
						flag = 1;
						break;
					}
					i++;
				}
			}
			if (flag)
				break;
		}
		i++;
	}
	i = pos;
	lenght_rest = 1;
	while (shell->command_line_clean[i++])
		lenght_rest++;
	tmp3 = ft_substr_clean(shell, shell->command_line_clean, pos, lenght_rest);
	return (ft_strjoin_clean(shell, tmp2, tmp3));
}

void resolve_dollar_plus_number(t_shell *shell)
{
	int b;

	b = 1;
	while (b)
	{
		shell->command_line_clean = replace_dollar_plus_number(shell);
		b = dollar_plus_number(shell);
	}
}

int extra_space(t_shell *shell)
{
	int i;
	int count;

	i = 0;
	while (shell->command_line_clean[i++] != ' ')
		if (shell->command_line_clean[i] == '\0')
			return (0);
	count = 1;
	if (shell->command_line_clean[i] == ' ')
		while (shell->command_line_clean[i++] == ' ')
			count++;
	if (count >= 2)
		return (1);
	return (0);
}

void operate_extra_space(t_shell *shell)
{
	int i;
	int pos;
	int lenght_rest;
	char *tmp1;
	char *tmp2;

	i = 0;
	while (shell->command_line_clean[i] != ' ')
		i++;
	tmp1 = ft_substr_clean(shell, shell->command_line_clean, 0, i + 1);
	while (shell->command_line_clean[i] == ' ')
		i++;
	lenght_rest = 0;
	pos = i;
	while (shell->command_line_clean[i++])
		lenght_rest++;
	tmp2 = ft_substr_clean(shell, shell->command_line_clean, pos, lenght_rest);
	shell->command_line_clean = ft_strjoin_clean(shell, tmp1, tmp2);
}

int	start_space(t_shell *shell)
{
	if (shell->command_line_clean[0] == ' ')
		return (1);
	return (0);
}

void	operate_start_space(t_shell *shell)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (shell->command_line_clean[i] == ' ')
		i++;
	count = i;
	j = 0;
	while (shell->command_line_clean[count])
	{
		count++;
		j++;
	}
	shell->command_line_clean = ft_substr_clean(shell, shell->command_line_clean, i, j);
}

void	loop_extra_space_outside_quotes(t_shell *shell)
{
	int i;
	int a;
	char *phrase;
	int bypass;

	bypass = 0;
	i = 0;
	phrase = shell->command_line_clean;
	while (i < (int)ft_strlen(phrase))
	{
		if (is_quote(phrase[i]))
			bypass = !bypass;

		a = i;
		if (bypass == 0 && phrase[i] == ' ' && phrase[i + 1] == ' '){
			while (phrase[a] == ' '){
				a++;
			}
			phrase = ft_strjoin_clean(shell, ft_substr_clean(shell, phrase, 0, i + 1), ft_substr_clean(shell, phrase, a, (int)ft_strlen(phrase)));
			i = 0;
		}
		i++;
	}
	shell->command_line_clean = phrase;
}

int		is_index_is_between_quote(int index, t_shell *shell)
{
	char *phrase;
	int inside;
	int f_i;
	int i;
	int a;

	f_i = 0;
	a = 0;
	inside = 0;
	i = 0;
	phrase = shell->command_line_clean;
	while (i < (int)ft_strlen(phrase))
	{
		if (is_quote(phrase[i]))
		{
			inside = !inside;
			if (inside)
				f_i = i;
			if (index > f_i && index < (f_i + a))
				return (1);
		}
		if (inside)
			a++;
		else
			a = 0;
		i++;
	}
	return (0);
}

void parse_command(t_shell *shell)
{
	int *each_cmd_lenght;
	int i;

	if (shell->command_line_clean == NULL)
		return;
	loop_extra_space_outside_quotes(shell);
	if (start_space(shell))
		operate_start_space(shell);
	if (have_vaguellette(shell))
		resolve_vaguellette(shell);
	if (dollar_plus_number(shell))
		resolve_dollar_plus_number(shell);
	if (have_env_variables(shell))
		resolve_replace_key_to_value_env(shell);
	shell->nbr_cmd = get_number_of_commands(shell);
	each_cmd_lenght = get_each_cmd_lenght(shell, shell->nbr_cmd);
	shell->tab_cmd = (char **)ft_safe_malloc((shell->nbr_cmd + 1) * sizeof(char *), shell);
	fill_cmd_array(shell, each_cmd_lenght);
	i = 0;
	while (i < shell->nbr_cmd)
	{
		if (start_and_end_quotes(shell->tab_cmd[i]))
		{
			execute_cmd(shell, shell->tab_cmd[i]);
			return;
		}
		i++;
	}
	shell->command_line_clean = check_if_quotes(shell, shell->command_line_clean);
	execute(shell);
}

void parser(t_shell *shell)
{
	shell->fd = 0;
	if (shell->command_line_clean != NULL)
		parse_command(shell);
	if (shell->fd != 0)
		close(shell->fd);
}
