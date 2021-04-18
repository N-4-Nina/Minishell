#include "../../includes/nsh.h"

void    clear_one(void)
{
    write(0, "\b", 1);
    write(0, " ", 1);
    //write(0, &nul, 1);
    write(0, "\b", 1);
}
void    inp_clear(t_inp *inp, int buf)
{
    int i;

    i = 0;
    while (inp->pos < inp->size)
    {
        gen_move(1, RIGHT);
        if (inp->buf[inp->pos] >= 0)
            inp->pos++;
        else
            inp->pos += utf_size(inp->buf[inp->pos]);
    }
    while (i < inp->size)
    {
        clear_one();
        if (inp->buf[i] >= 0)
            i++;
        else
            i += utf_size(inp->buf[i]);
    }
    i = 0;
    if (buf)
        while (i < ARG_MAX)
            inp->buf[i++] = 0;
}