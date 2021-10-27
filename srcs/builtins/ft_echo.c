#include "../includes/minishell.h"

int		get_flag(char *each_cmd)
{
	int		n_flag;

	n_flag = 0;
	if (each_cmd[5] == '-' && each_cmd[6] == 'n')
		n_flag = 1;
	return (n_flag);
}

void	ft_echo(t_shell *shell, char *cmd)
{
	int		n_flag;
	int		i;

	(void)(shell);

	if (ft_strcmp(cmd, "echo") == 0)
	{
		printf("\n");
		return ;
	}
	n_flag = get_flag(cmd);
	if (n_flag)
		i = 8;
	else
		i = 5;
	while (cmd[i])
		printf("%c", cmd[i++]);
	if (n_flag == 0)
		printf("\n");
}
