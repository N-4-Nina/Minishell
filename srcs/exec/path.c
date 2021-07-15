#include "../../includes/nsh.h"

/* need to determine if path is already specified (meaning if cmd contains a "/")*/

int set_abs_path(t_smpl *s, char *name)
{
    struct  stat    buf;

    if (!stat(name, &buf))
    {
        s->path = ft_strdup(name);
        free(name);
        // free_array(split, j);
        // free(path);
        // free(name);
        return (1);
    }
    return (0);
}

int set_cmd_path(t_smpl *s, t_env *env, char *name)
{
    int     i;
    int     j;
    char    **split;
    char    *path;
    char    *new;
    struct  stat    buf;

    i = 0;
    j = 0;
    if (name[0] == '/')
        return (set_abs_path(s, name));
    new = ft_strjoin("/", name);
    free(name);
    name = new;
    split = ft_split(find_by_name(env, "PATH")->value, ':');
    while (split[j])
        j++;
    while (split[i])
    {
        if (split[i][ft_strlen(split[i])-1] == '/')
            split[i][ft_strlen(split[i])-1] = 0;
        path = ft_strjoin(split[i], name);        
        if (!stat(path, &buf))
        {
            s->path = ft_strdup(path);
            free_array(split, j);
            free(path);
            free(name);
            return (1);
        }
        else
            free(path);
        i++;
    }
    free(name);
    free_array(split, j);
    return (0);
}