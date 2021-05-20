#include "../../includes/nsh.h"

void    gen_move(int nb, char dir)
{
    char    *itoa;
    char    esc;

    if (nb < 0)
        nb = -nb;
    esc = 27;
    itoa = ft_itoa(nb);
    write(1, &esc, 1);
    write(1, "[", 1);
    write(1, itoa, ft_strlen(itoa));
    write(1, &dir, 1);
    free(itoa);
    return ;
}

int handle_del(t_inp *inp)
{
    if (inp->pos == 0)
        return (-1);
    if (inp->buf[inp->pos-1] > 0)
    {
        if (inp->pos == inp->size)
            ascii_del_last(inp);
        else
            ascii_del(inp);
    }
    else
    {
        if (inp->pos == inp->size)
            utf_del_last(inp);
        else
            utf_del(inp);
    }
    return (1);
}

void    utf_skip(t_inp *inp, int dir)
{
    int i;
    i = 0;
    if (dir < 0)
    {
        i = utf_rev_size(inp, inp->pos);        
        inp->pos += dir * i;
        gen_move(1, LEFT);
    }
    else
    {
        i = utf_size(inp->buf[inp->pos]);
        inp->pos += dir * i;
        gen_move(1, RIGHT);
    }

}
void    switch_row(t_inp *inp, int dir)
{
    if (dir == -1)
    {    
        inp->curY--;
        inp->curX = inp->winX - 1;
        gen_move(1, UP);
        gen_move(inp->curX, RIGHT);
    }
    else
    {
        inp->curY++;
        gen_move(inp->curX, LEFT);
        inp->curX = 0;
        gen_move(1, DOWN);
        
    }
}

void    move_cursor(t_inp *inp, int dir)
{
    if (inp->buf[inp->pos + dir] < 0)
        return (utf_skip(inp, dir));
    inp->pos += dir;
    if ((inp->curX == 0 && dir == -1) || (inp->curX == inp->winX - 1 && dir == 1))
    {
        switch_row(inp, dir);
        return;
    }
    inp->curX += dir;
    if (dir == -1)
        gen_move(dir, LEFT);
    else
        gen_move(dir, RIGHT);
}

int handle_escape(t_inp *inp)
{
    char buf[2];

    read(0, buf, 2);
    if (buf[0] == '[' && (buf[1] >= 'A' && buf[1] <= 'D'))
        dispatch_arrow(inp, buf[1]);
    return (1);
    
}

int handle_spec_char(t_inp *inp, char c)
{
    if (c == 127)
        return (handle_del(inp));
    else if (c == 27)
        return (handle_escape(inp));    
    return (0);
}

int inp_read(t_inp *inp)
{
    int  check;
    char buf[1];

    while ((check = read(0, &buf, 1)))
    {
        if (handle_spec_char(inp, buf[0]))
            continue;
        else if (buf[0] == '\n')
        {   
            write(1, &buf[0], 1);
            return (1);
        }
        else if (buf[0] < 0)
            utf_handle_char(inp, buf[0]);
        else
            ascii_handle(inp, buf[0]);
    }
    return (check);
}
void    inp_reset(t_inp *inp)
{
    int i;

    i = 0;
    while (inp->buf[i])
        inp->buf[i++] = 0;
    inp->pos = 0;
    inp->size = 0;
    inp->his->pos = -1;
}

int get_input(t_sh *nsh)
{
    int r;

    r = 0;
    enableRawMode(nsh->term);
    inp_read(nsh->inp);
    if ((*nsh->inp->buf))
    {
        nsh->lex->inp = ft_strdup(nsh->inp->buf);
        new_entry(nsh->lex->inp, nsh->inp->his);
        r = 1;
    }
    inp_reset(nsh->inp);
    disableRawMode(nsh->term);
    return (r);
}