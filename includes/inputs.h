#ifndef INPUTS_H
# define INPUTS_H

#include "history.h"

#define HISTSIZE 500

typedef struct s_history
{
	char	*tl[HISTSIZE];
	int		pos;
	int		size;
}				t_his;

typedef	struct s_input
{
	char	buf[ARG_MAX];
	char	*cpy;
	t_his	*his;
	int		pos;
	int		size;
	int		promptsize;
}				t_inp;

int    dispatch_arrow(t_inp *inp, char c);
void    move_cursor(t_inp *inp, int dir);
void    gen_move(int nb, char dir);

int new_entry(char *new, t_his *h);

void    utf_handle_char(t_inp *inp, char c);
void    utf_del(t_inp *inp, char nul, char space);
int    utf_size(char b);

#endif