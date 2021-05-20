#include "../../includes/nsh.h"

/* need to determine if path is already specified (meaning if cmd contains a "/")*/


int set_cmd_path(t_smpl *s, t_env *env, char *name)
{
    int     i;
    char    **split;
    char    *path;
    struct  stat    buf;

    i = 0;
    name = ft_strjoin("/", name);
    split = ft_split(find_by_name(env, "PATH")->value, ':');
    while (split[i])
    {
        if (split[i][ft_strlen(split[i])-1] == '/')
            split[i][ft_strlen(split[i])-1] = 0;
        path = ft_strjoin(split[i], name);        
        if (!stat(path, &buf))
        {
            s->path = ft_strdup(path);
            free_array(split);
            free(path);
            return(1);
        }
        i++;
    }
    free_array(split);
    free(path);
    return (0);
}