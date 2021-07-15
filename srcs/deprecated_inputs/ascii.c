#include "../../includes/nsh.h"

void    ascii_del(t_inp *inp)
{
    //char    *new;
    int i;

    inp->buf[inp->pos-1] = 0;
    ft_strlcat(inp->buf, &inp->buf[inp->pos], inp->size-1);
    //new = ft_strdup(inp->buf);
    inp->pos--;
    inp->size--;
    i = inp->size;
    inp_clear(inp, 0);
    write(1, inp->buf, inp->size);

    while (i-- > inp->pos)
        gen_move(1, LEFT);
}

void    ascii_del_last(t_inp *inp)
{
    clear_one();
    inp->pos--;
    inp->size--;
    inp->buf[inp->pos] = 0;
}

void    ascii_append(t_inp *inp, char c)
{
    inp->buf[inp->pos] = c;
    write(1, &c, 1);
    inp->pos++;
    inp->size++;
    if (inp->curX == inp->winX-1)
    {
        inp->curX = 0;
        inp->curY++;
    }
    else
        inp->curX++;
}

void    ascii_insert(t_inp *inp, char c)
{
    int     i;
    char    *prev;

    i = 0;
    prev = ft_strdup(&inp->buf[inp->pos]);
    write(1, &c, 1);
    inp->buf[inp->pos] = c;
    inp->pos++;
    while (prev[i])
    {
        inp->buf[inp->pos + i] = prev[i];
        i++;
    }
    write(1, prev, ft_strlen(prev));
    gen_move(ft_strlen(prev), LEFT);
    free(prev);
    
    inp->size++;
}

void    ascii_handle(t_inp *inp, char c)
{
    if (inp->buf[inp->pos+1] == 0)
        ascii_append(inp, c);
    else
        ascii_insert(inp, c);
}