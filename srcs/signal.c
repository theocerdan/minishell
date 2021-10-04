#include "../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		//signal(SIGINT, signal_handler);
    }
}

void	signal_listeners(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
