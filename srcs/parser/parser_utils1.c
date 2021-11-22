/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:29:14 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:29:15 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_number_of_commands(t_shell *shell)
{
	int	nbr_cmd;
	int	i;

	i = 0;
	nbr_cmd = 1;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '|' && !is_index_is_between_quote(i, shell))
			nbr_cmd++;
		i++;
	}
	return (nbr_cmd);
}

int	check_chiant_norminette(t_shell *shell, int i)
{
	if ((shell->command_line_clean[i + 1] == ' ' && (shell->command_line_clean[i + 2] == '|' && !is_index_is_between_quote(i + 2, shell))) || shell->command_line_clean[i + 1] == '\0')
		return (1);
	return (0);
}

int	*get_each_cmd_lenght(t_shell *shell, int nbr_cmd)
{
	int		*each_cmd_lenght;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	count = 1;
	each_cmd_lenght = (int *)malloc((nbr_cmd + 1) * sizeof(int));
	while (shell->command_line_clean[i])
	{
		if (check_chiant_norminette(shell, i))
		{
			each_cmd_lenght[j] = count;
			count = 0;
			j++;
		}
		if (shell->command_line_clean[i] == ' '
			&& shell->command_line_clean[i + 1] == '|'
			&& shell->command_line_clean[i + 2] == ' '
			&& !is_index_is_between_quote(i + 1, shell))
			i = i + 3;
		count++;
		i++;
	}
	return (each_cmd_lenght);
}

void	fill_cmd_array(t_shell *shell, int *each_cmd_lenght)
{
	int		milestone;
	int		i;
	int		j;

	i = 0;
	j = 0;
	milestone = 0;
	while (shell->command_line_clean[i])
	{
		if ((shell->command_line_clean[i + 1] == '|'  && !is_index_is_between_quote(i + 1, shell)) || shell->command_line_clean[i + 1] == '\0')
		{
			shell->tab_cmd[j] = ft_substr(shell->command_line_clean,
					milestone, each_cmd_lenght[j]);
			milestone = i + 3;
			j++;
		}
		i++;
	}
}
