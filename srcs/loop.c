#include "../includes/nsh.h"

int	nsh_loop(t_sh *nsh)
{
	int		status;

	status = 1;
	while (status)
	{
		set_sig_behav(INTERACTIVE);
		build_prompt(nsh->env, nsh->inp);
		nsh->lex->inp = readline(nsh->inp->prompt);
		if(!nsh->lex->inp)
		{
			free(nsh->inp->prompt);
			break;
		}
		if (nsh->lex->inp[0])
			add_history(nsh->lex->inp);
		if (!lex_build(nsh->lex))
			continue;
		parse(nsh);
		exec(nsh);
		nsh_reset(nsh);
		
	}
	nsh_clear(nsh);
	return (status);
}
