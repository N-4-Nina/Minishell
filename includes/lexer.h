#ifndef LEXER_H
# define LEXER_H

# include "structures.h"

void	lex_init(t_lex *l);
void	lex_reset(t_lex *l);
int		lex_build(t_lex *l, char *prompt);
int		count_tokens(t_lex *l);
void	set_quote_len(t_lex *l);
void	set_spec_len(t_lex *l);
void	set_word_len(t_lex *l);
void	progress(t_lex *l, int add);
int		lex_inbound(t_lex lex);
int		lex_isover(t_lex lex);
void	handle_blank(t_lex *l);
void	handle_quote(t_lex *l);
void	handle_spec(t_lex *l);
void	handle_word(t_lex *l);
void	abort_token(t_lex *l);
void	free_tokens(char **tokens);
void	token_init(t_tok *tok);
int		set_spec_type(t_lex *l);
void	copy_data(t_lex *l, int add);

#endif