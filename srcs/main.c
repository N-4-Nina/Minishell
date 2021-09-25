/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/09/25 12:08:15 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "utils.h"
#include "environment.h"
#include "astree.h"
#include "nsh.h"
#include "lexer.h"
#include "signals.h"
#include "arrays.h"

int	nsh_clear(t_sh *nsh)
{
	int	ret;

	ret = *nsh->last_status;
	free(nsh->lex);
	free(nsh->inp);
	free_array(nsh->bui->str, 7);
	free(nsh->bui);
	free(nsh->last_status);
	env_clear(nsh->env);
	display_error("exit\n", "", "");
	return (ret);
}

void	nsh_reset(t_sh *nsh)
{
	free(nsh->inp->prompt);
	ast_reset(&(nsh->ast));
	lex_reset(nsh->lex);
}

void	reset_sig_catcher(void)
{
	g_sig_catcher[0] = 0;
	g_sig_catcher[1] = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_sh	nsh;
	int		exit;

	(void)argc;
	(void)argv;
	nsh_init(&nsh, envp);
	exit = nsh_loop(&nsh);
	return (exit);
}
