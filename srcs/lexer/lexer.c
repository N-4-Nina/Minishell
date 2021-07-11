/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/07/11 17:21:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* note to self -and others-:
 * Not only is the lexer different from parser,
 * but it comes before it and enables it.
 * Building a lexer supie we tokenize the input string,
 * specifying a type for each token. 
 * -Lexer distinguish between tokens, stores them,
 * and for each one answers the question:
 * "what is it ?" wheareas
 * -Parser, knowing what is what and obeying 
 * a defined grammar answers the question:
 * "can this type of token be here ?"
 * 
 * The Lexer should also probably check if some quotes 
 * are still open at the end of the command
 */

#include "../includes/nsh.h"

void	copy_data(t_lex *l, int add)
{
	l->t[l->j].data = (char *)malloc(l->t[l->j].len + add);
	if (!l->t[l->j].data)
		return (abort_token(l));
	ft_strlcpy(l->t[l->j].data, &l->inp[l->i], l->t[l->j].len + add);
}

int	tokenize(t_lex *l)
{
	l->i = 0;
	l->j = 0;
	while (l->inp[l->i])
	{
		token_init(&l->t[l->j]);
		if (isQuote(l->inp[l->i]))
			handle_quote(l);
		else if (isBlank(l->inp[l->i]))
			handle_blank(l);
		else if (isSpec(l->inp[l->i]))
			handle_spec(l);
		else if (!isSpec(l->inp[l->i]))
			handle_word(l);
	}
	return (1);
}

void	lex_reset(t_lex *l)
{
	l->i = 0;
	l->j = 0;
	if (l->inp)
		free(l->inp);
	l->nt--;
	while (l->nt >= 0)
	{
		if (l->t[l->nt].type == PIPE)
			free(l->t[l->nt].data);
		l->nt--;
	}
	l->nt = 0;
	if (l->t)
		free(l->t);
}

void	lex_init(t_lex *l)
{
	l->inp = NULL;
	l->t = NULL;
	l->nt = 0;
	l->i = 0;
	l->j = 0;
}

int	lex_build(t_lex *l)
{
	if (!l->inp)
		return (0);
	if (count_tokens(l) <= 0)
		return (0);
	l->t = malloc(sizeof(t_tok) * l->nt);
	tokenize(l);
	l->i = 0;
	return (l->nt);
}
