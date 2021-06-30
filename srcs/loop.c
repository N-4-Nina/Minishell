#include "../includes/nsh.h"

int	nsh_loop(t_sh *nsh)
{
	int		status;

	status = 1;
	while (status)
	{
		build_prompt(nsh->env, nsh->inp);
		nsh->lex->inp = readline(nsh->inp->prompt);
		if(!nsh->lex->inp)
			continue;
		if (nsh->lex->inp[0])
			add_history(nsh->lex->inp);
		if (!lex_build(nsh->lex))
			continue;
		parse(nsh);
		exec(nsh);
		nsh_reset(nsh);
		
	}
	nsh_clear(nsh);
	return(status);
}
