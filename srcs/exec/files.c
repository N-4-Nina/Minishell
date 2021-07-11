#include "../../includes/nsh.h"

int     here_doc(t_smpl *s, char *hd, char *end)
{
    char	*line;
	int		fd;
	size_t	endsize;
    size_t	max;

	if (s->hasheredoc)
		unlink(hd);
	endsize = ft_strlen(end);
	fd = open(hd, O_CREAT | O_WRONLY | O_APPEND, 0660);
	if (fd < 0)
	{
		printf("%d\n", fd);
		printf("%s\n", strerror(errno));
	}
    line = readline(">");
    max = ft_strlen(line);
    if (max < endsize)
        max = endsize;
    while (ft_strncmp(line, end, max))
    {
        if (!line)
            break;
        write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
        free(line);
        line = readline(">");
        max = ft_strlen(line);
        if (max < endsize)
            max = endsize;
    }
    s->hasheredoc = 1;
	close(fd);
	fd = open(hd, FLAGS_LESS, 0660);
	s->files[s->filesnb++] = fd;
	s->input = fd;
	unlink(hd);
	return (1);
}

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

int     open_file(t_smpl *s, char *file, char *hd, int flags)
{
    int fd;

    if (flags < 0)
        return (here_doc(s, hd, file));
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
        if (flags == (FLAGS_DGREAT) || flags == (FLAGS_GREAT))
            s->output = fd;
        else
            s->input = fd;
    }
    return (fd);
}