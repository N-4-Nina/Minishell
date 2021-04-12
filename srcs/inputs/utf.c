#include "../../includes/nsh.h"

void    utf_append(t_inp *inp, char *c, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        write(1, &c[i], 1);
        inp->buf[inp->pos++] = c[i++];
    }
    //inp->pos++;
    inp->size+=size;
}

void    utf_insert(t_inp *inp, char *c, int size)
{
    int     i;
    char    *prev;

    i = 0;
    prev = ft_strdup(&inp->buf[inp->pos]);
    
    while (i < size)
    {
        write(1, &c[i], 1);
        inp->buf[inp->pos++] = c[i++];
    }
    //inp->pos++;
    i = 0;
    while (prev[i])
    {
        inp->buf[inp->pos + i] = prev[i];
        i++;
    }
    write(1, prev, ft_strlen(prev));
    gen_move(ft_strlen(prev), LEFT);
    free(prev);
    
    inp->size+=size;
}

int    utf_size(char b)
{
    static unsigned char byte[8];
    unsigned char i;
    int j;

    i = 0;
    j = 0;
    while(i < 8)
    {
        byte[i] = '0' + ((b & (1 << i)) > 0);
        i++;
    }
    while (byte[--i] == '1')
        j++;
    return (j);
}

void    utf_del(t_inp *inp, char nul, char space)
{
    int i;

    i = 0;
    while (inp->buf[inp->pos - i] < 0 && i < 4)
        i++;
    write(0, "\b", i);
    write(0, &space, i);
    write(0, &nul, i);
    write(0, "\b", i);
    while(i > 0)
    {
        inp->pos--;
        inp->size--;
        inp->buf[inp->pos - i] = 0;
        i--;
    }
}

void    utf_handle_char(t_inp *inp, char c)
{
    char ar[4];
    int     size;
    int     i;

    (void)inp;
    size = utf_size(c);
    i = 1;
    ar[0] = c;
    while(i < size)
    {
        read(0, &ar[i], 1);
        i++;
    }
    if (inp->buf[inp->pos+1] == 0)
        utf_append(inp, ar, size);
    else
        utf_insert(inp, ar, size);

}