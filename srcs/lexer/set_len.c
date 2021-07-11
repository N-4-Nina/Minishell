/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/07/11 17:26:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void	set_quote_len(t_lex *l)
{
	char	matching;

	matching = l->inp[l->i];
	l->t[l->j].len = 1;
	while (l->inp[l->i + l->t[l->j].len]
		&& l->inp[l->i + l->t[l->j].len] != matching)
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
