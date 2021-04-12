#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef	struct s_lex
{
	char	*inp;
	t_tok 	*t;
	int		nt;
	int		i;
	int		j;
}				t_lex;

/*
 *lexer.c and related
*/
void lex_init(t_lex *l);
void  lex_reset(t_lex *l);
int  lex_build(t_lex *l);
int	count_tokens(t_lex *l);
void	set_quote_len(t_lex *l);
void	set_spec_len(t_lex *l);
void	set_word_len(t_lex *l);
int		lex_inbound(t_lex lex);
int		lex_isover(t_lex lex);


#endif