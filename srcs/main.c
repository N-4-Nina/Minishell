/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 17:32:45 by chpl             ###   ########.fr       */
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

int	main(void)
{
	t_sh	nsh;

	nsh_init(&nsh);
	nsh_loop(&nsh);
	return (0);
}
