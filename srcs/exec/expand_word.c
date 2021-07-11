#include "../includes/nsh.h"

void    do_cat(char **dst, char *src)
{
    int len;
    char    *tmp;

    if (!*dst)
    {
        *dst = ft_strdup(src);
        return;
    }
    len = ft_strlen(*dst) + ft_strlen(src) + 1;
    tmp = ft_strdup(*dst);
    free(*dst);
    *dst = malloc(len);
    ft_strlcpy(*dst, tmp, ft_strlen(tmp) + 1) ;
    ft_strlcat(*dst, src, len);
    free(tmp);
}

int     replace_var(char **dst, char *src, t_env *env)
{
    t_env   *var;
    int     i;

    i = 1;
    if (src[i + 1])
        return (replace_status());
    while (src[i] && !(isBlank(src[i])) && src[i] != '"')
        i++;
    var = find_by_name(env, ft_substr(src, 1 , i - 1));
    if (!var)
        return (i);
    do_cat(dst, var->value);
    return (i);
}

int     replace_strong(char **dst, char *src)
{
    int i;

    i = 1;
    while (src[i] && src[i] != '\'')
        i++;
    do_cat(dst, ft_substr(src, 1, i));
    return (i + 1);
}

int     replace_weak(char **dst, char *src, t_env *env)
{
    int i;
    char    single[2];

    i = 1;
    single[1] = 0;
    while (src[i] && src[i] != '"')
    {
        if (src[i] == '\\')
        {
            do_cat(dst, ft_substr(src, i, 1));
            i += 2;
        }
        else if (src[i] == '$')
            i += replace_var(dst, &src[i], env);
        else
        {
            single[0] = src[i];
            do_cat(dst, &single[0]);
            i++;
        }
    }
    return (i + 1);
}

char    *expand_word(char *s, t_env *env)
{
    int     i;
    char    *new;
    char    single[2];

    i = 0;
    single[1] = 0;
    new = NULL;
    while (s[i])
    {
        if (s[i] == '\'')
            i += replace_strong(&new, &s[i]);
        else if (s[i] == '"')
            i += replace_weak(&new, &s[i], env);
        else if (s[i] == '$')
            i += replace_var(&new, &s[i], env);
        else if (s[i] == '\\')
        {
            do_cat(&new, ft_substr(s, i, 1));
            i += 2;
        }
        else
        {
            single[0] = s[i];
            do_cat(&new, &single[0]);
            i++;
        }
    }
    return (new);
}