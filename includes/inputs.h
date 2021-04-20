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
	int		curX;
	int 	curY;
	int		winX;
	int		winY;
	int		promptsize;
}				t_inp;

int    dispatch_arrow(t_inp *inp, char c);
void    move_cursor(t_inp *inp, int dir);
void    gen_move(int nb, char dir);

void    inp_clear(t_inp *inp, int buf);
void    clear_one(void);

int new_entry(char *new, t_his *h);

void    ascii_handle(t_inp *inp, char c);
void	ascii_del(t_inp *inp);
void	ascii_del_last(t_inp *inp);

void    cursor_to_end(t_inp *inp);
void    set_new_cur(t_inp *inp);


void    utf_handle_char(t_inp *inp, char c);
void    utf_del(t_inp *inp);
void	utf_del_last(t_inp *inp);
int		utf_rev_size(t_inp *inp, int pos);
int    utf_size(char b);
int		charnb(char *s);

#endif