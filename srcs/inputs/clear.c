#include "../../includes/nsh.h"

void    clear_one(void)
{
    write(0, "\b", 1);
    write(0, " ", 1);
    //write(0, &nul, 1);
    write(0, "\b", 1);
}

void    cursor_to_end(t_inp *inp)
{
    while (inp->pos < inp->size)
    {
        if (inp->curX == inp->winX -1)
        {
            gen_move(1, DOWN);
            gen_move(inp->winX-1, LEFT);
            inp->curX = 0;
            inp->curY++;
        }
        else
        {
            gen_move(1, RIGHT);
            inp->curX++;
        }
        if (inp->buf[inp->pos] > 0)
            inp->pos++;
        else
            inp->pos += utf_size(inp->buf[inp->pos]);
    }
}

void    buf_clear(t_inp *inp)
{
    int i;

    i = 0;
    while (i < ARG_MAX)
            inp->buf[i++] = 0;
}

void    inp_clear(t_inp *inp, int buf)
{
    if (inp->size == 0)
        return;
    cursor_to_end(inp);
    while (inp->curY || (!inp->curY && inp->curX > inp->promptsize))
    {
        if (inp->curX == 0)
        {
            clear_one();
            gen_move(1, UP);
            gen_move(inp->winX-1, RIGHT);
            write(1, " ", 1);
            inp->curX = inp->winX-1;
            inp->curY--;
        }
        else
        {
            clear_one();
            inp->curX--;
        }
    
    }    
    if (buf)
        buf_clear(inp);
        
}