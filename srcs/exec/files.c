#include "../../includes/nsh.h"

void    close_files(t_smpl *s)
{
	while (s->filesnb > 0)
	{
		s->filesnb--;
		close(s->files[s->filesnb]);
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
	char	*hdcopy;

	hdcopy = ft_strdup(hd);
	if (flags < 0)
        return (here_doc(s, hdcopy, file));

	fd = open(file, flags, 0660);
	if (fd < 0)
	{
		printf("%s \n",strerror(errno));
		return (-1);
	}
	if (fd > -1)
	{
		s->files[s->filesnb] = fd;
		s->filesnb++;
		if (flags == (FLAGS_DGREAT) || flags == (FLAGS_GREAT))
            s->output = fd;
        else
            s->input = fd;
	}
	return(fd);
}