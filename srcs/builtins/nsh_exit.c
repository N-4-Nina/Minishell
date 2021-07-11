#include "../includes/nsh.h"

void	free_everything(t_sh *nsh)
{
	cmd_reset((t_cmd *)nsh->cmd);
	free_array(nsh->bui->str, 7);
	ast_reset(&nsh->ast);
	free(nsh->inp->prompt);
	env_clear(nsh->env);
	lex_reset(nsh->lex);
	free(nsh->lex);
	free(nsh->inp);
	free(nsh->bui);
}

int	nsh_exit(t_sh *nsh, char **args)
{
	free_everything(nsh);
	(void)args;
	exit(EXIT_SUCCESS);
	return (0);
}
