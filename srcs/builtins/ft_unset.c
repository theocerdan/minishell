#include "../includes/minishell.h"

int process_unset(char *cmd)
{
    (void)(cmd);
    printf("process_unset\n");
    return (1);
}

////////////////////////////////////////////////////////

void    ft_unset(t_shell *shell, char *each_cmd)
{
    char	*first_arg;

	first_arg = get_first_arg(each_cmd);
	if (ft_strlen(first_arg) > 0)
		ft_delete_var(first_arg, shell);
}
