/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_set_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:03:06 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 14:53:43 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/utils.h"
#include "../includes/lexer.h"

void	set_quote_len(t_lex *l)
{
	char	matching;

	matching = l->inp[l->i];
	l->t[l->j].len = 1;
	while (l->inp[l ->i + l->t[l->j].len]
		&& l->inp[l ->i + l->t[l->j].len] != matching)
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
	while (l->inp[l->i + l->t[l->j].len]
		&& !(isBlank(l->inp[l->i + l->t[l->j].len]))
		&& !(isSpec(l->inp[l->i + l->t[l->j].len])))
		l->t[l->j].len++;
}
