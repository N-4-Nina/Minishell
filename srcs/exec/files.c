/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 10:11:45 by chpl              #+#    #+#             */
/*   Updated: 2021/08/25 10:57:39 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"
#include "../includes/defines.h"

void	close_files(t_smpl *s)
{
	while (s->filesnb > 0)
	{
		s->filesnb--;
		close(s->files[s->filesnb]);
	}
	free(s->files);
}

int	get_flags(char *red)
{
	if (ft_strlen(red) == 2 && red[0] == '>')
		return (FLAGS_DGREAT);
	else if (red[0] == '>')
		return (FLAGS_GREAT);
	else if (ft_strlen(red) == 2 && red[0] == '<')
		return (FLAGS_DLESS);
	else
		return (FLAGS_LESS);
}

int	open_file(t_smpl *s, char *file, char *hd, int flags)
{
	int		fd;
	char	*hdcopy;

	if (flags < 0)
	{
		hdcopy = ft_strdup(hd);
		return (here_doc(s, hdcopy, file));
	}
	fd = open(file, flags, 0660);
	if (fd < 0)
	{
		printf("Nsh: file: %s \n", strerror(errno));
		s->output = -1;
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
	return (fd);
}
