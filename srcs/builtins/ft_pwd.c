#include "../includes/minishell.h"

int process_pwd(char *cmd)
{
    (void)(cmd);
    printf("process_pwd\n");
    //printf("%s\n", get_env_value("PWD", shell), shell);
    return (1);
}

//////////////////////////////////////////////////////////

void	ft_pwd(void)
{
	char	*cwd;
	char	*buffer;

	buffer = NULL;
	cwd = getcwd(buffer, 0);
	if (cwd)
		printf("%s\n", cwd);
	else
		ft_error("minishell: error pwd\n");
	free(cwd);
}
