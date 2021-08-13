/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:27:05 by chpl              #+#    #+#             */
/*   Updated: 2021/08/13 08:38:04 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/lexer.h"

void	lex_reset(t_lex *l)
{
	l->i = 0;
	l->j = 0;
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
}
