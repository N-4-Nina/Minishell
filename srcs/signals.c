#include "../includes/nsh.h"

void	interactive_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signum == SIGQUIT)
    {
        NULL;
    }
}

void    set_sig_behav(int mode)
{
    if (mode == INTERACTIVE)
    {
        signal(SIGINT, interactive_handler);
        signal(SIGQUIT, interactive_handler);
    }
    else if (mode == RESET)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
    else if (mode == IGNORE)
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
    }
}