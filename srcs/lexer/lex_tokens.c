/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:26:16 by chpl              #+#    #+#             */
/*   Updated: 2021/08/08 09:55:48 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void	abort_token(t_lex *l)
{
	while (l->j > 0)
	{
		free(l->t[l->j].data);
		l->j--;
	}
}

void	token_init(t_tok *tok)
{
	tok->data = NULL;
	tok->len = 0;
	tok->type = -1;
}
