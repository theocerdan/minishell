#include "../includes/minishell.h"

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

////////////////////////////////////////////////////////////

void	redisplay_prompt(int sig)
{
	(void)(sig);
	printf("\n");
}

void	define_input_signals(void)
{
	signal(SIGINT, redisplay_prompt);
	signal(SIGQUIT, SIG_IGN);
}
