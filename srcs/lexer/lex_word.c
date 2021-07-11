/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:17:08 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 17:22:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void	handle_quote(t_lex *l)
{
	set_quote_len(l);
	l->t[l->j].type = WORD;
	copy_data(l, 2);
	progress(l, 1);
}

void	handle_word(t_lex *l)
{
	set_word_len(l);
	l->t[l->j].type = WORD;
	copy_data(l, 1);
	progress(l, 0);
}
