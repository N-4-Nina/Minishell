#ifndef TOKEN_H
#define TOKEN_H


typedef	enum	e_token_type
{
	DGREAT,
	GREAT,
	DLESS,
	LESS,
	PIPE,
	SEMI,
	WORD,
}					t_ttype;

typedef	struct s_token
{
	int				len;
	t_ttype 		type;
	char			*data;
}				t_tok;
#endif