#include "../includes/nsh.h"

void	sigint_handler(int signum)
{
	printf("Caught signal %d\n",signum);
	// Cleanup and close up stuff here

    //kill
	// Terminate program
    if (signum == 2)
        exit(signum);
}

void    sigquit_handler(int signum)
{
    // CTRL + \""
    printf("Caught signal %d\n",signum);
}

void    set_sig_behav(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}