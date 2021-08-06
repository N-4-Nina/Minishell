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
		write(1, "\b\b  \b\b", 6);
	}
}

void	catch_signal(int signum)
{
	g_sig_catcher[0] = 1;
	g_sig_catcher[1] = signum;
	if (signum == 3 || signum == 4 || signum == 6 || signum == 8 || signum == 11)
		printf("Core Dumped.\n");
}

void	set_sig_status(int *status)
{
	*status = 128 + g_sig_catcher[1];
	reset_sig_catcher();
}

void    set_sig_behav(int mode)
{
	int	i;

	i = 0;
	if (mode == INTERACTIVE)
	{
		while (i < _NSIG)
		{
			signal(i, SIG_DFL);
			i++;
		}
		signal(SIGINT, interactive_handler);
		signal(SIGQUIT, interactive_handler);
	}
	else if (mode == RESET)
	{
		while (i < 15)
		{
			signal(i, SIG_DFL);
			i++;
		}
	}
	else if (mode == CATCH)
	{
		while (i < 15)
		{
			signal(i, catch_signal);
			i++;
		}
		//signal(SIGINT, SIG_IGN);
		//signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
	}
}