#ifndef ASTREE_H
#define ASTREE_H

#define AST_LEFT 0
#define AST_RIGHT 1

#include "token.h"

typedef	enum	e_node_type
{
	N_PROGRAM = 0,
	N_CMD,
	N_CMD_SUFFIX,
	N_IO_FILE,
	N_PIPE_SEQ,
	N_SIMPLE_CMD,
	N_WORD,
	N_RED
}					t_ntype;

typedef	struct	s_ast
{
	char	*data;
	int		len;
	t_ntype	type;
	struct	s_ast	*left;
	struct	s_ast	*right;
}				t_ast;


t_ast   *new_node(t_ntype type, char *datas);
t_ast   *node_from_tok(t_tok tok);
void    free_node(t_ast *node);
void     graft_node_left(t_ast **node, t_ast *new);
void     graft_node_right(t_ast **node, t_ast *new);
void    ast_reset(t_ast **node);


#endif