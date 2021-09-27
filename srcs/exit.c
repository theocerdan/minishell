#include "../includes/minishell.h"

int process_exit(t_shell *shell, char *cmd)
{
    (void)(shell);
    (void)(cmd);
    exit(0);
    return (1);
}
