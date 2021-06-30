#include "../../includes/nsh.h"

void    set_new_cur(t_inp *inp)
{
    int i;

    i = 0;
    inp->curX = inp->promptsize;
    inp->curY = 0;
    while (i < inp->size)
    {
        if (inp->curX == inp->winX)
        {
            inp->curX = 0;
            inp->curY++;
        }
        else
            inp->curX++;
        
        if (inp->buf[i] > 0)
            i++;
        else
            i += utf_size(inp->buf[i]);
    }
    
}