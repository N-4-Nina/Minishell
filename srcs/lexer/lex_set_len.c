/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_set_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:03:06 by chpl              #+#    #+#             */
/*   Updated: 2021/09/01 11:04:38 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/utils.h"
#include "../includes/lexer.h"
#include "../includes/libs.h"

void	set_quote_len(t_lex *l)
{
	char	matching;

	matching = l->inp[l->i + l->t[l->j].len];
	l->t[l->j].len += 1;
	while (l->inp[l ->i + l->t[l->j].len]
		&& l->inp[l ->i + l->t[l->j].len] != matching)
		l->t[l->j].len++;
	l->t[l->j].len++;
}

void	set_spec_len(t_lex *l)
{
	if ((l->inp[l->i] == '>' && l->inp[l->i + 1] == '>')
		|| (l->inp[l->i] == '<' && l->inp[l->i + 1] == '<'))
		l->t[l->j].len = 2;
	else
		l->t[l->j].len = 1;
}

void	set_word_len(t_lex *l)
{
	while (l->i + l->t[l->j].len < l->inp_size
		&& !(is_blank(l->inp[l->i + l->t[l->j].len]))
		&& !(is_spec(l->inp[l->i + l->t[l->j].len])))
	{
		if (l->inp[l->i + l->t[l->j].len] == '\\')
			l->t[l->j].len += 2;
		else if (is_quote(l->inp[l->i + l->t[l->j].len]))
			set_quote_len(l);
		else
			l->t[l->j].len++;
	}
}
