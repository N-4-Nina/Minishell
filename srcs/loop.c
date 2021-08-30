/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:20:15 by chpl              #+#    #+#             */
/*   Updated: 2021/08/28 17:57:57 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/signals.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/exec.h"
#include "../includes/nsh.h"
#include "../includes/defines.h"
#include "../includes/prompt.h"
#include "../includes/utils.h"
#include "../includes/builtins.h"

int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!isBlank(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	loop_signal(t_sh *nsh)
{
	int caught;

	if (g_sig_catcher[0])
	{
		caught = g_sig_catcher[1];
		set_sig_status(nsh->last_status);
		if (caught == SIGTERM)
			return (1);
		if (caught == SIGSEGV)
			nsh_exit(nsh, NULL);
	}
	return (0);
}

void	process_input(t_sh *nsh)
{
	if (!is_empty(nsh->lex->inp))
		add_history(nsh->lex->inp);
	if (!lex_build(nsh->lex, nsh->inp->prompt))
		return ;
	if (!parse(nsh))
	{
		nsh_reset(nsh);
		return ;
	}
	exec(nsh);
	nsh_reset(nsh);
	return ;
}

int	nsh_loop(t_sh *nsh)
{
	int		status;

	status = 1;
	while (status)
	{
		set_sig_behav(INTERACTIVE);
		build_prompt(nsh->env, nsh->inp);
		nsh->lex->inp = readline(nsh->inp->prompt);
		if (!nsh->lex->inp || loop_signal(nsh))
		{
			free(nsh->inp->prompt);
			break ;
		}
		process_input(nsh);
	}
	return (nsh_clear(nsh));
}
