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

void    append_char(t_inp *inp, char c)
{
    inp->buf[inp->pos] = c;
    write(1, &c, 1);
    inp->pos++;
    inp->size++;
}

void    insert_char(t_inp *inp, char c)
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

int handle_del(t_inp *inp)
{
    char nul;
    char space;

    space = 32;
    nul = 0;
    if (inp->pos > 0)
    {

        write(0, "\b", 1);
        write(0, &space, 1);
        write(0, &nul, 1);
        write(0, "\b", 1);
        inp->pos--;
        inp->size--;
        inp->buf[inp->pos] = 0;  
        return (1);
    }
    else
        utf_del(inp, nul, space);
    return (1);
}

void    utf_skip(t_inp *inp, int dir)
{
    int i;
    i = 0;
    if (dir < 0)
    {
        while (inp->buf[inp->pos - i] < 0 && i < 4)
            i++;        
        inp->pos += dir * (i+1);
        gen_move(dir * i, LEFT);
    }
    else
    {
        i = utf_size(inp->buf[inp->pos]);
        inp->pos += dir * (i+1);
        gen_move(dir * i, RIGHT);
    }

}
void    move_cursor(t_inp *inp, int dir)
{
    //should check if char is > 0, if so do as usual
    //else, should find the utf size and skip it. 
    if (inp->buf[inp->pos + dir] < 0)
        return (utf_skip(inp, dir));
    inp->pos += dir;
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

void    handle_char(t_inp *inp, char c)
{
    if (inp->buf[inp->pos+1] == 0)
        append_char(inp, c);
    else
        insert_char(inp, c);
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
            handle_char(inp, buf[0]);
    }
    return (check);
}

int get_input(t_sh *nsh)
{
    int i;

    i = 0;
    if (inp_read(nsh->inp))
    {
        nsh->lex->inp = ft_strdup(nsh->inp->buf);
        new_entry(nsh->lex->inp, nsh->inp->his);
    }
    while (nsh->inp->buf[i])
        nsh->inp->buf[i++] = 0;
    nsh->inp->pos = 0;
    nsh->inp->size = 0;
    nsh->inp->his->pos = -1;
    return (1);
}