/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 12:44:58 by abouchau          #+#    #+#             */
/*   Updated: 2020/11/17 14:30:52 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/nsh.h"

int	check_new_line(char *s)
{
	int i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	gnl_read(int fd, int check, int ret, char *still[FOPEN_MAX])
{
	char	*buffer;
	char	*temp;

	if (!(buffer = malloc(BUFFER_SIZE + 1)) || read(fd, buffer, 0) == -1)
		return (-1);
	while (check == -1 && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = 0;
		handleArrow(buffer);
		check = check_new_line(buffer);
		if (!still[fd] && ret > 0)
			still[fd] = ft_strjoin("", buffer);
		else if (ret > 0)
		{
			temp = ft_strdup(still[fd]);
			free(still[fd]);
			still[fd] = ft_strjoin(temp, buffer);
			free(temp);
		}
	}
	free(buffer);
	return (ret);
}

int	gnl_write(int fd, char **line, char *still[FOPEN_MAX])
{
	int			i;
	char		*temp;

	i = 0;
	while (still[fd][i] != '\n' && still[fd][i])
		i++;
	if (still[fd][i] == 0)
	{
		*line = ft_strdup(still[fd]);
		free(still[fd]);
		still[fd] = ft_strdup("");
		free(still[fd]);
		return (0);
	}
	else
	{
		*line = ft_substr(still[fd], 0, i);
		temp = ft_substr(still[fd], i + 1, ft_strlen(still[fd]) - i);
		free(still[fd]);
		still[fd] = ft_strdup(temp);
		free(temp);
	}
	return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static	char	*still[FOPEN_MAX];
	int				i;
	int				ret;
	int				check;

	i = 0;
	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	check = (still[fd]) ? check_new_line(still[fd]) : -1;
	if (gnl_read(fd, check, 1, still) == -1)
		return (-1);
	if (still[fd] && still[fd][0])
		ret = gnl_write(fd, line, still);
	else
	{
		*line = ft_strdup("\0");
		ret = 0;
	}
	return (ret);
}
