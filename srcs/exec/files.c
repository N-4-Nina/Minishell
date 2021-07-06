#include "../../includes/nsh.h"

void    close_files(t_smpl *s)
{
    while (s->filesnb > 0)
    {
        s->filesnb--;
        close(s->files[s->filesnb]);
        // printf("closing %d\n", s->files[s->filesnb]);
        // printf("ret = %d\n", close(s->files[s->filesnb]));    
    }
    free(s->files);
}

int     get_flags(char *red)
{
    if (ft_strlen(red) == 2 && red[0] == '>')
        return(FLAGS_DGREAT);
    else if (red[0] == '>')
        return(FLAGS_GREAT);
    else if (ft_strlen(red) == 2 && red[0] == '<')
        return(FLAGS_DLESS);
    else
        return(FLAGS_LESS);
}

int     open_file(t_smpl *s, char *file, int flags)
{
    int fd;

    fd = open(file, flags, 0660);
    if (fd < 0)
    {
        printf("%s\n",strerror(errno));
        return (-1);
    }
    if (fd > -1)
    {
        s->files[s->filesnb] = (int)malloc(sizeof(int));
        s->files[s->filesnb] = fd;
        s->filesnb++;
    }
    return(fd);
}