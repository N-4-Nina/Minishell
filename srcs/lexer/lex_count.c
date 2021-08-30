/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:44:04 by chpl              #+#    #+#             */
/*   Updated: 2021/08/28 10:56:53 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/lexer.h"
#include "../includes/utils.h"

int	count_quote(t_lex *l)
{
	char	matching[2];

	matching[0] = l->inp[l->i];
	matching[1] = 0;
	l->i++;
	while (l->inp[l->i] && l->inp[l->i] != matching[0])
		l->i++;
	if (!l->inp[l->i])
	{
		display_error("Nsh: did not find matching ", matching, " quote.\n");
		return (-1);
	}
	l->i++;
	return (1);
}

int	count_blank(t_lex *l)
{
	while (l->inp[l->i] && isBlank(l->inp[l->i]))
		l->i++;
	return (1);
}

int	count_spec(t_lex *l)
{
	if ((l->inp[l->i] == '>' && l->inp[l->i + 1] == '>')
		|| (l->inp[l->i] == '<' && l->inp[l->i + 1] == '<'))
		l->i += 2;
	else
		l->i += 1;
	l->nt++;
	return (1);
}

int	count_word(t_lex *l)
{
	while (l->i < l->inpSize && !(isBlank(l->inp[l->i]))
		&& !(isSpec(l->inp[l->i])))
	{
		if (isQuote(l->inp[l->i]))
		{
			if (count_quote(l) < 0)
				return (-1);
		}
		else
			l->i++;
	}
	l->nt++;
	return (1);
}

int	count_tokens(t_lex *l)
{
	int	r;

	while (l->i < l->inpSize)
	{
		if (l->inp[l->i] && isBlank(l->inp[l->i]))
			r = count_blank(l);
		else if (l->inp[l->i] && isSpec(l->inp[l->i]))
			r = count_spec(l);
		else if (l->inp[l->i] && !isSpec(l->inp[l->i]))
			r = count_word(l);
		if (r < 0)
		{
			l->i = 0;
			l->nt = 0;
			return (-1);
		}
	}
	return (r);
}
