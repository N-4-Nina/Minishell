#include "../../includes/nsh.h"

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
        set_new_cur(inp);
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
                set_new_cur(inp);
                write(0, &inp->buf, inp->pos + 1);
                free(inp->cpy);
            }
            else
            {
                while(inp->size >= 0)
                    inp->buf[inp->size--] = 0;
                inp->pos = 0;
                //inp->size = 0;
                set_new_cur(inp);
            }
            return (1);            
        }
        ft_strlcpy(inp->buf, inp->his->tl[inp->his->pos], ft_strlen(inp->his->tl[inp->his->pos]) + 1);
        inp->pos = ft_strlen(inp->buf);
        inp->size = inp->pos;
        set_new_cur(inp);
        write(1, &inp->buf, inp->pos + 1);
        return (1);
    }
    return (0);
}