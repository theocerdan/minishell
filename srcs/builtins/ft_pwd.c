#include "../includes/minishell.h"

int process_pwd(char *cmd)
{
    (void)(cmd);
    printf("process_pwd\n");
    //printf("%s\n", get_env_value("PWD", shell), shell);
    return (1);
}
