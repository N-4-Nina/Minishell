/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 10:39:49 by chappelle         #+#    #+#             */
/*   Updated: 2021/08/10 15:03:58 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"
#include "../includes/signals.h"
#include "../includes/defines.h"

int	check_heredoc(char **hd)
{
	int	fd;

	fd = 0;
	*hd = update_heredoc_name(*hd);
	printf("from check = %s \n", *hd);
	if (!*hd)
	{
		printf("Please set the HEREDOC variable.\n");
		return (0);
	}
	fd = open(*hd, FLAGS_DGREAT, 0660);
	if (fd < 0)
	{
		printf("%s\n", *hd);
		printf("HEREDOC file must be accessible to this program.\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	hd_write(int fd, char **line, char *end, size_t *max)
{
	size_t	endsize;

	endsize = ft_strlen(end);
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	free(*line);
	*line = readline("> ");
	if (!*line)
	{
		printf("\nnsh: Warning: here-document ended \
with EOF instead of \"%s\"\n", end);
		return (0);
	}
	*max = ft_strlen(*line);
	if (*max < endsize)
		*max = endsize;
	return (1);
}

void	hd_read(t_smpl *s, int fd, char *end)
{
	size_t	max;
	size_t	endsize;
	char	*line;

	set_sig_behav(RESET);
	endsize = ft_strlen(end);
	line = readline("> ");
	if (!line)
		printf("\nnsh: Warning: here-document ended \
with EOF instead of \"%s\"\n", end);
	max = ft_strlen(line);
	if (max < endsize)
		max = endsize;
	while (ft_strncmp(line, end, max))
	{
		if (!hd_write(fd, &line, end, &max))
			break ;
	}
	free(line);
	s->hasheredoc = 1;
	close(fd);
	exit(EXIT_SUCCESS);
}

void	hd_parent(t_smpl *s, char *hd, int fd, int *status)
{
	set_sig_behav(HD_CATCH);
	waitpid(0, status, WUNTRACED);
	fd = open(hd, FLAGS_LESS, 0660);
	s->files[s->filesnb++] = fd;
	s->input = fd;
	unlink(hd);
	if (g_sig_catcher[0])
	{
		write(1, "\n", 1);
		close(fd);
	}
	if (g_sig_catcher[0] && g_sig_catcher[1] == SIGINT)
		s->output = -1;
	reset_sig_catcher();
	free(hd);
}

int	here_doc(t_smpl *s, char *hd, char *end)
{
	int		status;
	int		fd;
	pid_t	pid;

	if (!check_heredoc(&hd))
		return (-1);
	if (s->hasheredoc)
		unlink(hd);
	fd = open(hd, O_CREAT | O_WRONLY | O_APPEND, 0660);
	if (fd < 0)
		printf("%s\n", strerror(errno));
	pid = fork();
	if (!pid)
		hd_read(s, fd, end);
	else
		hd_parent(s, hd, fd, &status);
	return (1);
}
