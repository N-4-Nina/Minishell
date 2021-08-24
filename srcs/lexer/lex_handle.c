/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:30:49 by chpl              #+#    #+#             */
/*   Updated: 2021/08/24 15:24:53 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/utils.h"
#include "../includes/lexer.h"

void	handle_blank(t_lex *l)
{
	while (l->inp[l->i] && isBlank(l->inp[l->i]))
		l->i++;
}

void	handle_quote(t_lex *l)
{
	set_quote_len(l);
	l->t[l->j].type = WORD;
	copy_data(l, 2);
	progress(l, 0);
}

void	handle_spec(t_lex *l)
{
	set_spec_len(l);
	copy_data(l, 1);
	set_spec_type(l);
	progress(l, 0);
}

void	handle_word(t_lex *l)
{
	set_word_len(l);
	l->t[l->j].type = WORD;
	copy_data(l, 1);
	progress(l, 0);
}
