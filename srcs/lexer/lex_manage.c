/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:27:05 by chpl              #+#    #+#             */
/*   Updated: 2021/09/18 09:27:40 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "lexer.h"

void	lex_reset_syntax(t_lex *l)
{
	while (l->i <= l->nt)
	{
		if ((l->t[l->i].type >= DGREAT && l->t[l->i].type <= LESS)
			|| l->t[l->i].type == WORD)
			free(l->t[l->i].data);
		l->i++;
	}
}

void	lex_reset(t_lex *l)
{
	l->inp_size = 0;
	if (l->inp)
		free(l->inp);
	l->nt--;
	if (l->syntax_error)
		lex_reset_syntax(l);
	while (l->nt >= 0)
	{
		if (l->t[l->nt].type == PIPE || l->t[l->nt].type == SEMI)
			free(l->t[l->nt].data);
		l->nt--;
	}
	l->i = 0;
	l->j = 0;
	l->nt = 0;
	l->syntax_error = 0;
	if (l->t)
		free(l->t);
}

void	lex_init(t_lex *l)
{
	l->inp = NULL;
	l->t = NULL;
	l->nt = 0;
	l->i = 0;
	l->j = 0;
	l->inp_size = 0;
	l->syntax_error = 0;
}
