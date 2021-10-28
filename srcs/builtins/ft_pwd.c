#include "../includes/minishell.h"

void	ft_pwd(t_shell *shell, char *cmd)
{
	char	*cwd;
	char	*buffer;

	(void)(shell);
	(void)(cmd);
	buffer = NULL;
	cwd = getcwd(buffer, 0);
	if (cwd)
		printf("%s\n", cwd);
	else
		ft_error("minishell: error pwd\n");
	free(cwd);
}
