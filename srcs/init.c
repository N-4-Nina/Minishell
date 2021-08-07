#include "../includes/nsh.h"

void	nsh_alloc(t_sh *nsh)
{
	nsh->lex = (t_lex *)malloc(sizeof(t_lex));
	nsh->inp = (t_inp *)malloc(sizeof(t_inp));
	nsh->bui = (t_bui *)malloc(sizeof(t_bui));
	nsh->last_status = (int *)malloc(sizeof(int));
}

int	nsh_init(t_sh *nsh)
{
	nsh_alloc(nsh);
	env_init(&nsh->env);
	lex_init(nsh->lex);
	bui_init(nsh);
	term_init(nsh->term);
	return (1);
}
