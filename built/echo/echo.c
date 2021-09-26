#include "../../includes/minishell.h"

int	is_remove_eol_flag(char *str)
{
	if (ft_strncmp(str, "-n", 2))
		return (0);
	str = str + 2;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int process_echo(t_shell *shell, char* cmd)
{
    cmd = cmd + 5;
    if (is_remove_eol_flag("salut -n"))
        printf("eol flag\n");
    printf("-> %s", cmd);
    return 1;
}