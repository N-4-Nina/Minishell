#include "../../includes/nsh.h"

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
        inp_clear(inp, 1);
        ft_strlcpy(inp->buf, inp->his->tl[inp->his->pos], ft_strlen(inp->his->tl[inp->his->pos]) + 1);
        inp->pos = ft_strlen(inp->buf);
        inp->size = inp->pos;
        write(0, &inp->buf, inp->size + 1);
        return (1);
    }
    return (0);
}

int his_down(t_inp *inp)
{
    if (inp->his->pos > -1)
    {
        inp->his->pos--;
        inp_clear(inp, 1);
        if (inp->his->pos == -1)
        {
            if (inp->cpy)
            {
                ft_strlcpy(inp->buf, inp->cpy, ft_strlen(inp->cpy));
                inp->pos = ft_strlen(inp->buf);
                inp->size = inp->pos;
                write(0, &inp->buf, inp->pos + 1);
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
        inp->pos = ft_strlen(inp->buf);
        inp->size = inp->pos;
        write(1, &inp->buf, inp->pos + 1);
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