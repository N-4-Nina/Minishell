/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/07/11 16:57:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int	count_quote(t_lex *l)
{
	char	matching;

	 matching = l->inp[l->i];
	 l->i++;
	 while (l->inp[l->i] && l->inp[l->i] != matching)
		l->i++;
	if (!l->inp[l->i])
	{
		printf("did not find matching %c quote. \n", matching);
		return (-1);
	}
	l->i++;
	l->nt++;
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
	while (l->inp[l->i] && !(isBlank(l->inp[l->i])) && !(isSpec(l->inp[l->i])))
		l->i++;
	l->nt++;
	return (1);
}

int	count_tokens(t_lex *l)
{
	int	r;

	while (l->inp[l->i])
	{
		if (l->inp[l->i] && isQuote(l->inp[l->i]))
			r = count_quote(l);
		else if (l->inp[l->i] && isBlank(l->inp[l->i]))
			r = count_blank(l);
		else if (l->inp[l->i] && isSpec(l->inp[l->i]))
			r = count_spec(l);
		else if (l->inp[l->i] && !isSpec(l->inp[l->i]))
			r = count_word(l);
	}
	if (r < 0)
		return (-1);
	return (r);
}
