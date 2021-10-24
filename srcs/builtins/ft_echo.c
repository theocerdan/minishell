#include "../includes/minishell.h"

int		process_echo(char *cmd)
{
	(void)(cmd);
	printf("ECHO!!!\n");
	return (1);
}

//////////////////////////////////////////////////////////

int		get_flag(char *each_cmd)
{
	int		n_flag;

	n_flag = 0;
	if (each_cmd[5] == '-' && each_cmd[6] == 'n')
		n_flag = 1;
	return (n_flag);
}

void	ft_echo(char *each_cmd)
{
	int		n_flag;
	int		i;

	if (ft_strcmp(each_cmd, "echo") == 0)
	{
		printf("\n");
		return ;
	}
	n_flag = get_flag(each_cmd);
	if (n_flag)
		i = 8;
	else
		i = 5;
	while (each_cmd[i])
		printf("%c", each_cmd[i++]);
	if (n_flag == 0)
		printf("\n");
}
