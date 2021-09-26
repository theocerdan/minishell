#include "../../includes/minishell.h"

int process_pwd(t_shell *shell, char* cmd)
{
    printf("%s\n", get_env_value("PWD", shell), shell);
    return 1;
}