#include "../includes/nsh.h"

t_inter inter_init(int i)
{
    t_inter inter;

    inter.i = 0;
	inter.j = 0;
    inter.k = 0;
    inter.r = 0;
    inter.cmds = (char***)malloc(i * i * 2);
    while (inter.i < i)
	    inter.cmds[inter.i++] = malloc(sizeof(char **));
    inter.i = 0;
    inter.args = malloc(sizeof(int) * i);
	inter.red = malloc(sizeof(int) * i);
    return (inter);
}

t_trans trs_init(int i)
{
    t_trans trs;

    trs.quotes[0] = 0;
    trs.quotes[1] = 0;
    trs.dollar = 0;
    trs.back = 0;
    trs.new = 0;
    trs.skip = 0;
    trs.i = i;
    trs.str = malloc(sizeof(char *));
    trs.tmp = malloc(sizeof(char *));
    trs.str[0] = 0;

    return (trs);
}