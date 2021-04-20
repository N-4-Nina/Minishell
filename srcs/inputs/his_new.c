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

int new_entry(char *new, t_his *h)
{
    int i;
    
    if (h->size == HISTSIZE)
        cycle_new_entry(new, h);
    else
        add_new_entry(new, h);

    i = 0;
    while (i <= h->size)
    {
        printf("%s\n", h->tl[i]);
        i++;
    }
    return (1);
}