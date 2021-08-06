#include "../includes/nsh.h"

char	*update_heredoc_name(char *hd)
{
	struct	stat buf;
	int			last;
	int			i;
	char		*tmp;

	if (!hd)
		return (NULL);
	while (stat(hd, &buf) >= 0)
	{
		i = 0;
		last = ft_strlen(hd) - 1;
		if (hd[last] > 47 && hd[last] < 57)
			hd[last]++;
		else
		{
			if (hd[last] == 57)
			{
				while (hd[last - i] == 57)
					hd[last - i++] = '0';
				if (ft_isalpha(hd[last + i]))
					hd[last - i + 1] = 1;
				else
					hd[last - i + 1]++;
				tmp = hd;
				hd = ft_strjoin(hd, "0");
				free(tmp);
			}
			else
			{
				tmp = hd;
				hd = ft_strjoin(hd, "1");
				free(tmp);
			}
		}
	}
	return (hd);
}

int check_heredoc(char **hd)
{
    int fd;

    fd = 0;
	*hd = update_heredoc_name(*hd);
	printf("from check = %s \n", *hd);
    if (!*hd)
	{
		printf("Please set the HEREDOC variable.\n");
		return (0);
	}    
    fd = open(*hd, FLAGS_DGREAT,  0660);
    if (fd < 0)
	{
		printf("%s\n", *hd);
		printf("HEREDOC file must be accessible to this program.\n");
		return (0);
	}
    close(fd);
    return (1);
}

void    hd_read(t_smpl *s, int fd, char *end)
{
    size_t	max;
    size_t endsize;
    char *line;

    endsize = ft_strlen(end);
    //set_sig_behav(HEREDOC);
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
	free(line);
	s->hasheredoc = 1;
	close(fd);
    exit(EXIT_SUCCESS);
}

int     here_doc(t_smpl *s, char *hd, char *end)
{
	int     status;
	int		fd;
    pid_t   pid;
    pid_t   wpid;

	if (!check_heredoc(&hd))
		return (0);
	if (s->hasheredoc)
		unlink(hd);
	fd = open(hd, O_CREAT | O_WRONLY | O_APPEND, 0660);
	if (fd < 0)
	{
		printf("%d\n", fd);
		printf("%s\n", strerror(errno));
	}
    pid = fork();
    if (!pid)
        hd_read(s, fd, end);
    else
    {
        wpid = waitpid(0, &status, WUNTRACED);
        fd = open(hd, FLAGS_LESS, 0660);
	    s->files[s->filesnb++] = fd;
	    s->input = fd;
	    unlink(hd);
    }
	
	return (1);
}
