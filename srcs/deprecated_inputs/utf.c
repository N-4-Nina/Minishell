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
    inp->size+=size;
}
int    charnb(char *s)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(s[i])
    {
        if (s[i] > 0)
            i++;
        else
            i += utf_size(s[i]);
        j++;
    }
    return (j);
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
    gen_move(charnb(prev), LEFT);
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

int     utf_rev_size(t_inp *inp, int pos)
{
    int i;

    i = 1;
    while (inp->buf[pos-i-1] < 0)
        i++;
    while (utf_size(inp->buf[pos-i]) < i)
        i -= utf_size(inp->buf[pos-i]);
    return (i);
}

void    utf_del(t_inp *inp)
{
    int i;

    i = utf_rev_size(inp, inp->pos); // -1 ? 
}

void    utf_del_last(t_inp *inp)
{
    int i;

    i = utf_rev_size(inp, inp->pos);
    clear_one();
    while(i > 0)
    {
        inp->pos--;
        inp->size--;
        inp->buf[inp->pos] = 0;
        i--;
    }
    inp->buf[inp->pos] = 0;
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