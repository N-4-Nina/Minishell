/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 16:28:28 by chpl             ###   ########.fr       */
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

void	abort_token(t_lex *l)
{
	while (l->j > 0)
	{
		free(l->t[l->j].data);
		//l->t[l->j] = NULL;
		//free(l.t[l->j]);
		l->j--;
	}
	//empty_array(l);
}

void	progress(t_lex *l, int add)
{
	l -> i += l->t[l->j].len + add;
	l -> j++;
}

void	handle_blank(t_lex *l)
{
	while (l->inp[l->i] && isBlank(l->inp[l->i]))
		l->i++;
}

void	copy_data(t_lex *l, int add)
{
	if(!(l->t[l->j].data = (char *)malloc(l->t[l->j].len + add)))
	 	return (abort_token(l));
	ft_strlcpy(l->t[l->j].data, &l->inp[l->i], l->t[l->j].len + add);
}

void	handle_quote(t_lex *l)
{
	set_quote_len(l);
	l->t[l->j].type = WORD;
	copy_data(l, 2);
	progress(l, 1);
}
	
int	set_spec_type(t_lex *l)
{
	char 	types[4] = {'>', '<', '|', ';'};
	int		i;
	
	if (l->t[l->j].len == 2)
		return (l->t[l->j].type = DGREAT);
	i = 0;
	while (i < 4)
	{
		if (l->t[l->j].data[0] == types[i])
			return (l->t[l->j].type = i + 1);
		i++;
	}
	return (-1);
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

void	token_init(t_tok *tok)
{
	tok->data = NULL;
	tok->len = 0;
	tok->type = -1;
}
int	tokenize(t_lex *l)
{
        l->i = 0; //both should be in lex_clear
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
;        }
        return (1);
}  

void  lex_reset(t_lex *l)
{
    l->i = 0;
	l->j = 0;
	if (l->inp)
		free(l->inp);
	//l->nt--;
	
	// while (l->nt > 0)
	// {
	// 	if (l->t[l->nt].type == WORD)
	// 		free(l->t[l->nt].data);
	// 	l->nt--;
	// }
	l->nt = 0; //should be unecessary ??
	if (l->t)
		free(l->t);
}

void lex_init(t_lex *l)
{
	l->inp = NULL;
	l->t = NULL;
	l->nt = 0;
	l->i = 0;
	l->j = 0;
}

int	lex_inbound(t_lex lex)
{
	return (lex.i < lex.nt);
}

int	lex_isover(t_lex lex)
{
	return (lex.i >= lex.nt);
}

int  lex_build(t_lex *l)
{
	//if (!l->inp)
	//	return (0);
    if (count_tokens(l) <= 0)
		return (0);
	l->t = malloc(sizeof(t_tok) * l->nt);
	tokenize(l);
	l->i = 0;
	return (l->nt);
}