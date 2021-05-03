#include "../includes/nsh.h"

int	nsh_loop(t_sh *nsh)
{
	int		status;

	status = 1;
	while (status)
	{
		display_prompt(nsh->env, nsh->inp);

		//status = get_next_line(0, &(nsh->lex->inp));
		if(!get_input(nsh))
			continue;
		if (!lex_build(nsh->lex))
			continue;
		parse(nsh);
		exec(nsh);
		nsh_reset(nsh);
		
	}
	nsh_clear(nsh);
	return(status);
}
