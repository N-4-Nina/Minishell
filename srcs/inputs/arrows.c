#include "../../includes/nsh.h"

void    handle_lat_arrow(t_inp *inp, int dir)
{
    (void)inp;
    if (dir == -1 && inp->pos > 0)
        move_cursor(inp, dir);
    else if (dir == 1 && inp->pos < inp->size)
        move_cursor(inp, dir);
    else
        return;
}

void    handle_vert_arrow(t_inp *inp, int dir)
{
    (void)inp;
    (void)dir;
     if (dir == -1)
        his_up(inp);
     if (dir == 1)
        his_down(inp);
}

int    dispatch_arrow(t_inp *inp, char c)
{
    if (c == 'A')
        handle_vert_arrow(inp, -1);
    if (c == 'B')
        handle_vert_arrow(inp, 1);
    if (c == 'C')
        handle_lat_arrow(inp, 1);
    if (c == 'D')
        handle_lat_arrow(inp, -1);
    return (1);
}

