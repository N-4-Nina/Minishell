/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:51:48 by chpl              #+#    #+#             */
/*   Updated: 2021/08/21 11:14:46 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/defines.h"
#include "../includes/signals.h"

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
		write(1, "\b\b  \b\b", 6);
}

void	catch_signal(int signum)
{
	g_sig_catcher[0] = 1;
	g_sig_catcher[1] = signum;
	printf("catcher %d\n", signum);
	if (signum == 3 || signum == 4 || signum == 6
		||signum == 8)
		printf("Core Dumped.\n");
	else if (signum == 11)
		printf("Segmentation fault (core dumped)\n");
}

void	hd_catch_sig(int signum)
{
	g_sig_catcher[0] = 1;
	g_sig_catcher[1] = signum;
}

void	set_sig_status(int *status)
{
	*status = 128 + g_sig_catcher[1];
	reset_sig_catcher();
}

void	set_sig_behav(int mode)
{
	int	i;

	i = 0;
	if (mode == INTERACTIVE)
	{
		while (i < _NSIG)
			signal(i++, SIG_DFL);
		signal(SIGINT, interactive_handler);
		signal(SIGQUIT, interactive_handler);
	}
	else if (mode == RESET)
	{
		while (i < 15)
			signal(i++, SIG_DFL);
		signal(SIGSEGV, catch_signal);
	}
	else if (mode == CATCH)
	{
		while (i < 15)
			signal(i++, catch_signal);
	}
	else if (mode == HD_CATCH)
		while (i < 15)
			signal(i++, hd_catch_sig);
}
