#include "../includes/minishell.h"

void    signal_handler(int signal)
{
    (void)(signal);
    write(1, "\n", 1);
    //rl_replace_line("", 0);
    //rl_on_new_line();
    //rl_redisplay();
}

void    signal_listeners(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
