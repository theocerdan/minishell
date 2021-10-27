#include "../includes/minishell.h"

t_built	built[] = {
	{CD, "cd", &ft_cd},
	{ENV, "env", &ft_env},
	{PWD, "pwd", &ft_pwd},
	{EXPORT, "export", &ft_export},
	{UNSET, "unset", &ft_unset},
	{EXIT, "exit", &ft_exit},
	{ECHO, "echo", &ft_echo},
	{EXEC, "exec", NULL}
};

t_built	get_command_type(char *cmd)
{

	int i;

	i = 0;
	while (i < 8)
	{
		if (str_equals_ignore_case(built[i].cmd, cmd)){
			printf("trouvé %s\n", built[i].cmd);
			return (built[i]);
		}
		i++;
	}
	return (built[7]);
}
