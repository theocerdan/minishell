#include "../includes/minishell.h"

void	handle_signal(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	//-1 : attendre le processus enfant
	//status : Lorsque le processus enfant se termine, la valeur pid enfant est affectée
	//WNOHANG : Si le pid ne peut pas être récupéré car le processus enfant n'est pas terminé, 0 est renvoyé comme valeur de retour
	if (sig == SIGINT)
	{
		if (pid == -1) //pid == -1 : S'il n'y a pas de processus fils
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", 1);
	}
	else if(sig == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \b\b", 1);
		}
		else
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	define_input_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
