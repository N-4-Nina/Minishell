#include "../includes/nsh.h"

void	win_init(t_inp *inp)
{
	struct	winsize w;
	(void)inp;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	// inp->curY = 0;
	// inp->winX = w.ws_col;
	// inp->winY = w.ws_row;
	//printf("term dimension = %dx%d\n", inp->winX, inp->winY);
}

void inp_init(t_inp *inp)
{
	int	i;

	i = 0;
	(void)inp;
	// while (i < ARG_MAX)
	// 	inp->buf[i++] = 0;
	// inp->pos = 0;
	// inp->size = 0;
	// inp->cpy = NULL;
	// his_init(inp->his);
	win_init(inp);
}

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
	//inp_init(nsh->inp);
	bui_init(nsh);
	term_init(nsh->term);	
	return (1);
}