#include "../includes/minishell.h"

int	get_number_of_commands(t_shell *shell)
{
	t_token *cmd;
	t_list 	*start;
	int		nbr_cmd;

	nbr_cmd = 1;
	start = shell->token_list;
	while (shell->token_list)
	{
		cmd = (t_token*)shell->token_list->content;
		if (cmd->type == PIPE)
			nbr_cmd++;
		shell->token_list = shell->token_list->next;
	}
	shell->token_list = start;
	return (nbr_cmd);
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
		if (((shell->command_line_clean[i + 1] == ' ') && (shell->command_line_clean[i + 2] == '|')) || shell->command_line_clean[i + 1] == '\0')
		{
			each_cmd_lenght[j] = count;
			count = 0;
			j++;
		}
		if (shell->command_line_clean[i] == ' ' && shell->command_line_clean[i + 1] == '|' && shell->command_line_clean[i + 2] == ' ')
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
		if (shell->command_line_clean[i + 1] == '|' || shell->command_line_clean[i + 1] == '\0')
		{
			shell->tab_cmd[j] = ft_substr(shell->command_line_clean, milestone, each_cmd_lenght[j]);
			milestone = i + 3;
			j++;
		}
		i++;
	}
}
