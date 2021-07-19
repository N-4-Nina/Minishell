#include "../includes/nsh.h"

void	free_everything(t_sh *nsh)
{
	cmd_reset((t_cmd *)nsh->cmd);
	free_array(nsh->bui->str, 7);
	ast_reset(&nsh->ast);
	free(nsh->inp->prompt);
	free(nsh->inp->line);
	lex_reset(nsh->lex);
	free(nsh->lex);
	free(nsh->inp);
	free(nsh->bui);
}

int	nsh_exit(t_sh *nsh, char **args)
{
	int	exit_status;

	free_everything(nsh);
	if (args[1])
		exit_status = ft_atoi(args[1]);
	else
		exit_status = *nsh->last_status;
	free(nsh->last_status);
	exit(exit_status);
}
