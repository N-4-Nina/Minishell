/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:23:33 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 16:18:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"

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
