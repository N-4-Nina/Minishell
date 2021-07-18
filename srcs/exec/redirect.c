#include "../../includes/nsh.h"

void    recover_origin(int origin[2])
{
	dup2(origin[0], STDIN_FILENO);
	dup2(origin[1], STDOUT_FILENO);
}

void    redirect(t_smpl *s, int *ori_in, int *ori_out)
{
	*ori_in = dup(STDIN_FILENO);
	*ori_out = dup(STDOUT_FILENO);
	if (s->input != -1 && s->input != -1 && s->input != STDIN_FILENO)
		dup2(s->input, STDIN_FILENO);
	if (s->output != -1 && s->output != -1 && s->output != STDOUT_FILENO)
		dup2(s->output, STDOUT_FILENO);
}