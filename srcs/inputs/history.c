#include "../../includes/nsh.h"

void    inp_clear(t_inp *inp)
{
    int i;

    i = 1;
    while (inp->pos++ < inp->size)
        gen_move(1, 'C');
    while (i < inp->size)
    {
        write(1, "\b", 1);
        write(1, " ", 1);
        write(1, "\b", 1);
        i++;
    }
    i = 0;
    while (i < ARG_MAX)
        inp->buf[i++] = 0;
}

int add_new_entry(char *new, t_his *h)
{
    int i;

    i = h->size;
    while (i >= 0)
    {
        h->tl[i+1] = h->tl[i];
        i--;
    }
    h->tl[0] = ft_strdup(new);
    h->size++;
    return (1);
}

int cycle_new_entry(char *new, t_his *h)
{
    int i;

    i = HISTSIZE-2;
    free(h->tl[HISTSIZE - 1]);
    while (i > 0)
    {
        h->tl[i+1] = h->tl[i];
        i++;
    }
    h->tl[0] = ft_strdup(new);
    return (1);
}

void    his_init(t_his *h)
{
    h->size = -1;
    h->pos = -1;
}

int his_up(t_inp *inp)
{
    if (inp->his->pos < inp->his->size)
    {
        inp->his->pos++;
        if (inp->his->pos == 0 && inp->size > 0)
            inp->cpy = ft_strdup(inp->buf);
        inp_clear(inp);
        ft_strlcpy(inp->buf, inp->his->tl[inp->his->pos], ft_strlen(inp->his->tl[inp->his->pos]) + 1);
        inp->pos = ft_strlen(inp->buf) + 1;
        inp->size = inp->pos;
        write(1, &inp->buf, inp->size);
        return (1);
    }
    return (0);
}

int his_down(t_inp *inp)
{
    if (inp->his->pos > -1)
    {
        inp->his->pos--;
        inp_clear(inp);
        if (inp->his->pos == -1)
        {
            if (inp->cpy)
            {
                ft_strlcpy(inp->buf, inp->cpy, ft_strlen(inp->cpy));
                inp->pos = ft_strlen(inp->buf) + 1;
                inp->size = inp->pos;
                write(1, &inp->buf, inp->pos);
                free(inp->cpy);
            }
            else
            {
                while(inp->size >= 0)
                    inp->buf[inp->size--] = 0;
                inp->pos = 0;
            }
            return (1);            
        }
        ft_strlcpy(inp->buf, inp->his->tl[inp->his->pos], ft_strlen(inp->his->tl[inp->his->pos]) + 1);
        inp->pos = ft_strlen(inp->buf) + 1;
        inp->size = inp->pos;
        write(1, &inp->buf, inp->pos);
        return (1);
    }
    return (0);
}

int new_entry(char *new, t_his *h)
{
    if (h->size == HISTSIZE)
        cycle_new_entry(new, h);
    else
        add_new_entry(new, h);

    int i = 0;
    while (i <= h->size)
    {
        printf("%s\n", h->tl[i]);
        i++;
    }
    return (1);
}