/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:21:53 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 10:30:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/exec.h"
#include "../includes/environment.h"
#include "../includes/builtins.h"

void	nsh_alloc(t_sh *nsh)
{
	nsh->lex = (t_lex *)malloc(sizeof(t_lex));
	nsh->inp = (t_inp *)malloc(sizeof(t_inp));
	nsh->bui = (t_bui *)malloc(sizeof(t_bui));
	nsh->last_status = (int *)malloc(sizeof(int));
}

int	nsh_init(t_sh *nsh, char **envp)
{
	nsh_alloc(nsh);
	env_init(&nsh->env, envp);
	lex_init(nsh->lex);
	bui_init(nsh);
	return (1);
}
