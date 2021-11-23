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

void	resolve_dollar_plus_number(t_shell *shell)
{
	int	b;

	b = 1;
	while (b)
	{
		shell->command_line_clean = replace_dollar_plus_number(shell);
		b = dollar_plus_number(shell);
	}
}

void	loop_extra_space_outside_quotes(t_shell *shell)
{
	int		i;
	int		a;
	char	*phrase;
	int		bypass;

	bypass = 0;
	i = 0;
	phrase = shell->command_line_clean;
	while (i < (int)ft_strlen(phrase))
	{
		if (is_quote(phrase[i]))
			bypass = !bypass;
		a = i;
		if (bypass == 0 && phrase[i] == ' ' && phrase[i + 1] == ' ')
		{
			while (phrase[a] == ' ')
				a++;
			phrase = ft_strjoin_clean(shell, ft_substr_clean(shell, phrase, 0,
						i + 1), ft_substr_clean(shell, phrase, a,
						(int)ft_strlen(phrase)));
			i = 0;
		}
		i++;
	}
	shell->command_line_clean = phrase;
}

void	process_parse(t_shell *shell)
{
	loop_extra_space_outside_quotes(shell);
	if (start_space(shell))
		operate_start_space(shell);
	if (have_vaguellette(shell))
		resolve_vaguellette(shell);
	if (dollar_plus_number(shell))
		resolve_dollar_plus_number(shell);
	if (have_env_variables(shell))
		resolve_replace_key_to_value_env(shell);
}

void	parse_command(t_shell *shell)
{
	int	*each_cmd_lenght;
	int	i;

	if (shell->command_line_clean == NULL)
		return ;
	process_parse(shell);
	shell->nbr_cmd = get_number_of_commands(shell);
	each_cmd_lenght = get_each_cmd_lenght(shell, shell->nbr_cmd);
	shell->tab_cmd = (char **)ft_safe_malloc((shell->nbr_cmd + 1)
			* sizeof(char *), shell);
	fill_cmd_array(shell, each_cmd_lenght);
	i = 0;
	while (i < shell->nbr_cmd)
	{
		if (start_and_end_quotes(shell->tab_cmd[i]))
		{
			execute_cmd(shell, shell->tab_cmd[i]);
			return ;
		}
		i++;
	}
	shell->command_line_clean = check_if_quotes(shell,
			shell->command_line_clean);
	execute(shell);
}

void	parser(t_shell *shell)
{
	shell->fd = 0;
	if (shell->command_line_clean != NULL)
		parse_command(shell);
	if (shell->fd != 0)
		close(shell->fd);
}
