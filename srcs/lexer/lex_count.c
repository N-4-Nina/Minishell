/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 09:44:04 by chpl              #+#    #+#             */
/*   Updated: 2021/08/24 11:29:51 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/lexer.h"
#include "../includes/utils.h"

int	count_quote(t_lex *l, int isNew)
{
	char	matching;

	matching = l->inp[l->i];
	l->i++;
	while (l->inp[l->i] && l->inp[l->i] != matching)
		l->i++;
	if (!l->inp[l->i])
	{
		printf("Nsh: did not find matching %c quote. \n", matching);
		return (-1);
	}
	l->i++;
	if (isNew)
		l->nt++;
	if (l->inp[l->i] && !isBlank(l->inp[l->i]))
		return (count_word(l, 0));
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

int	count_word(t_lex *l, int isNew)
{
	while (l->i < l->inpSize && !(isBlank(l->inp[l->i]))
		&& !(isSpec(l->inp[l->i])))
	{
		if (isQuote(l->inp[l->i]))
			if (count_quote(l, 0) < 0)
				return (-1);
		l->i++;
	}
	if (isNew)
		l->nt++;
	return (1);
}

int	count_tokens(t_lex *l)
{
	int	r;

	while (l->i < l->inpSize - 1)
	{
		if (l->inp[l->i] && isQuote(l->inp[l->i]))
			r = count_quote(l, 1);
		else if (l->inp[l->i] && isBlank(l->inp[l->i]))
			r = count_blank(l);
		else if (l->inp[l->i] && isSpec(l->inp[l->i]))
			r = count_spec(l);
		else if (l->inp[l->i] && !isSpec(l->inp[l->i]))
			r = count_word(l, 1);
		if (r < 0)
		{
			l->i = 0;
			l->nt = 0;
			return (-1);
		}
	}
	return (r);
}
