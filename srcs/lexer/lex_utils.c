/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 17:13:21 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 17:16:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

void	progress(t_lex *l, int add)
{
	l -> i += l->t[l->j].len + add;
	l -> j++;
}

int	lex_inbound(t_lex lex)
{
	return (lex.i < lex.nt);
}

int	lex_isover(t_lex lex)
{
	return (lex.i >= lex.nt);
}
