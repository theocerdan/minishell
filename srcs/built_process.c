#include "../includes/minishell.h"

t_built	built[] = {
	{CD, "cd", &process_cd},
	{ENV, "env", &process_env},
	{PWD, "pwd", &process_pwd},
	{EXPORT, "export", &process_export},
	{UNSET, "unset", &process_unset},
	{EXIT, "exit", &process_exit},
	{ECHO, "echo", &process_echo}
};

int	get_command_type(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (str_equals_ignore_case(built[i].cmd, cmd->full_cmd))
			return (built[i].id);
		i++;
	}
	return (EXEC);
}
