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

////////////////////////////////////////////////////////////////////////

void	interrupt_process(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	quit_process(int signal)
{
	(void)signal;
	printf("Quit (core dumped)\n");
}

void	define_exec_signals(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}
