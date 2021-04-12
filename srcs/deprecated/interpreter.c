/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 16:28:28 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int     isMeta(char c)
{
    	return (c== '<' || c == '>' || 
		c == '|' || c == ';');
}

void    update_state(t_trans *trs, char *token)
{
    if (trs->back == 1)
        return;
    if (token[0] == '\\')
    {
        trs->back = 1;
        trs->skip = 1;
    }
    if (token[0] == '\'' && !(trs->quotes[1]))
        toggle(0, trs);
    if (token[0] == '\"' && !(trs->quotes[0]))
        toggle(1, trs);
    if (isBlank(token[0]) && !(trs->quotes[0]) && !(trs->quotes[1]))
    {
        trs->new = 1;
        trs->skip = 1;
    }
    if (token[0] == '$' && !(trs->quotes[0]) && !(trs->back))
    {
        trs->dollar = 1;
        trs->skip = 1;
    }
    if (token[0] == '<' && !(trs->quotes[0]) && !(trs->quotes[1]) && !(trs->back))
    {
        trs->inf = 1;
        trs->skip = 1;
    }
}

void    do_cat(t_trans *trs, char *str)
{
    int len;

    len = ft_strlen(trs->str) + ft_strlen(str) + 1;
    trs->tmp = ft_strdup(trs->str);
    free(trs->str);
    trs->str = malloc(len);
    ft_strlcpy(trs->str, trs->tmp, ft_strlen(trs->tmp) + 1) ;
    ft_strlcat(trs->str, str, len);
    //trs->str[len] = 0;
    free(trs->tmp);
}

void    replace_var(t_trans *trs, char *token)
{
    t_env   *var;

    var = find_by_name(token);
    if (!var)
        return;
    do_cat(trs, var->value);
    trs->dollar = 0;
}

void    handle_blank(t_trans *trs, char *token)
{
    int len;

    len = 0;
    if (trs->quotes[0] || trs->quotes[1])
        do_cat(trs, token);
    //else
    //    do_cat(trs, " ");
    
}

void    update_string(t_trans *trs, char *token)
{
    if (trs->dollar)
        replace_var(trs, token);
    // if (trs->inf)
    //     replace_file(trs, token);
    else if (isBlank(token[0]))
        handle_blank(trs, token);
    else
        do_cat(trs, token);
    
}

void    translate(char **tokens, t_inter *in)
{  
    t_trans trs;

    trs = trs_init();
    while (tokens[in->i] && !isMeta(tokens[in->i][0]))
    {
        update_state(&trs, tokens[in->i]);
        if (trs.new && trs.str[0] && trs.skip)
        {
            in->cmds[in->j][in->k] = ft_strdup(trs.str);
            free(trs.str);
            trs.str = malloc(1);
            trs.str[0] = 0;
            trs.new = 0;
            in->k++;
        }
        if (!trs.skip)
            update_string(&trs, tokens[in->i]);
        else
            trs.skip = 0;
        in->i++;
    }
    if (*trs.str)
        in->cmds[in->j][in->k++] = ft_strdup(trs.str);
    free(trs.str);
    return;
}

void    store_red(char **tokens, t_inter *in)
{

    if (!(ft_strncmp(tokens[in->i], "|", 1)))
        in->red[in->r] = 1;
    else if (!(ft_strncmp(tokens[in->i], ">>", 2)))
        in->red[in->r] = 3;
    else if (!(ft_strncmp(tokens[in->i], ">", 1)))
        in->red[in->r] = 2;
    else if (!(ft_strncmp(tokens[in->i], "<", 1)))
        in->red[in->r] = 4;
    in->r++;
    in->i++;
}

void    set_seq(t_inter *in, t_seq *s)
{
    int i;

    s->cmdnb = in->j;
    s->argnb = (int *)malloc(sizeof(int) * s->cmdnb);
    s->rednb = in->r;
    s->red = in->red;
    //in->cmds[in->j][in->k] = NULL;
    i = 0;
    while (i < s->cmdnb)
    {
        s->argnb[i] = in->args[i] - 1;
        i++;
    }
}

int     interpret(char **tokens, int toknb)
{
    t_inter in;
    t_seq   s;

    in = inter_init(toknb);
    while (tokens[in.i])
    {
        while (tokens[in.i] && ft_strncmp(tokens[in.i], ";", 1))
        {
            while (isBlank(tokens[in.i][0]))
                in.i++;
            in.cmds[in.j][in.k++] = ft_strdup(tokens[in.i++]);
            translate(tokens, &in);
            in.args[in.j] = in.k;
            in.k = 0;
            in.j++;
            if (tokens[in.i])
                store_red(tokens, &in);
            else
                set_seq(&in, &s);
        }
        //execution comes here

        /*this part is for testing */
        
        in.k = 0;
        in.j = 0;
        in.r = 0;
        while (in.j < s.cmdnb)
            {
                printf("cmd : %s\n", in.cmds[in.j][0]);
                printf(  "argnb = %d\n", s.argnb[in.j]);
                while (in.k < s.argnb[in.j])
                {
                    printf("   arg : %s\n", in.cmds[in.j][in.k+1]);
                    in.k++;
                }
                printf("       redirection: %d\n", in.red[in.r]);
                in.r++;
                in.k = 0;
                in.j++;
            }
    }
    return (0);
}