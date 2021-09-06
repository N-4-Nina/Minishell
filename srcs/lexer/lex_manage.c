/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:27:05 by chpl              #+#    #+#             */
/*   Updated: 2021/09/06 10:40:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "lexer.h"

void	lex_reset(t_lex *l)
{
	l->i = 0;
	l->j = 0;
	l->inp_size = 0;
	if (l->inp)
		free(l->inp);
	l->nt--;
	while (l->nt >= 0)
	{
		if (l->t[l->nt].type == PIPE || l->t[l->nt].type == SEMI)
			free(l->t[l->nt].data);
		l->nt--;
	}
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
