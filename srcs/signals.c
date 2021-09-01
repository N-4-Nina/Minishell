/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:51:48 by chpl              #+#    #+#             */
/*   Updated: 2021/09/01 08:16:26 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/defines.h"
#include "../includes/signals.h"
#include "../includes/utils.h"
#include "../includes/builtins.h"

void	interactive_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		catch_signal(SIGINT);
	}
	else if (signum == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

void	set_interactive(void)
{
	int	i;

	i = -1;
	while (++i < _NSIG)
		signal(i, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTERM, catch_signal);
	signal(SIGINT, interactive_handler);
	signal(SIGQUIT, interactive_handler);
}

void	set_catch(char *cmd)
{
	int	i;

	i = -1;
	while (++i < _NSIG)
	{
		if (i == SIGINT || i == SIGQUIT)
			signal(i, catch_signal);
		else if (i == 15 || i == 18 || i == 20
			|| i == 21 || i == 22 || i == 23 || i == 28)
			signal(i, SIG_IGN);
		else
			signal(i, SIG_DFL);
	}
	if (cmd && !ft_strncmp(cmd, "kill", 5))
		signal(SIGQUIT, SIG_IGN);
}

void	set_sig_behav(int mode, char *cmd)
{
	int	i;

	i = -1;
	if (mode == INTERACTIVE)
		set_interactive();
	else if (mode == RESET)
		while (++i < _NSIG)
			signal(i++, SIG_DFL);
	else if (mode == CATCH)
		set_catch(cmd);
	else if (mode == HD_CATCH)
		while (++i < _NSIG)
			if (i != SIGCHLD)
				signal(i, catch_signal);
}
