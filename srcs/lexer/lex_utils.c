/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:23:33 by chpl              #+#    #+#             */
/*   Updated: 2021/08/08 09:54:37 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int	lex_inbound(t_lex lex)
{
	return (lex.i < lex.nt);
}

int	lex_isover(t_lex lex)
{
	return (lex.i >= lex.nt);
}

void	progress(t_lex *l, int add)
{
	l -> i += l->t[l->j].len + add;
	l -> j++;
}
