#include "../includes/minishell.h"

void	exec_cmd(char *path, char **cmd, char **envp)
{
	pid_t	pid = 0;
	int		status = 0;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) {
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else {
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(path, cmd, envp) == -1){
			printf("execve: %s\n", path);
			perror("shell");
		}
		exit(EXIT_FAILURE);
	}
}