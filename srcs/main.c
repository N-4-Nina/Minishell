/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 10:33:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/utils.h"
#include "../includes/environment.h"
#include "../includes/astree.h"
#include "../includes/nsh.h"
#include "../includes/lexer.h"
#include "../includes/signals.h"

void	nsh_clear(t_sh *nsh)
{
	free(nsh->lex);
	free(nsh->inp);
	free_array(nsh->bui->str, 7);
	free(nsh->bui);
	free(nsh->last_status);
	env_clear(nsh->env);
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

	(void)argc;
	(void)argv;
	nsh_init(&nsh, envp);
	nsh_loop(&nsh);
	return (0);
}
