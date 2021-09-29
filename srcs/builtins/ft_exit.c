#include "../includes/minishell.h"

int process_exit(char *cmd)
{
    (void)(cmd);
    exit(0);
    return (1);
}
