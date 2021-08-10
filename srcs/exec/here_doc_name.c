/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 10:44:37 by chappelle         #+#    #+#             */
/*   Updated: 2021/08/10 15:01:06 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/exec.h"

void	increment_filename(char **hd, int last, int *i)
{
	char		*tmp;

	if ((*hd)[last] > 47 && (*hd)[last] < 57)
		(*hd)[last] = *hd[last] + 1;
	else
	{
		if ((*hd)[last] == 57)
		{
			while ((*hd)[last - *i] == 57)
				(*hd)[last - *i++] = '0';
			if (ft_isalpha((*hd)[last + *i]))
				(*hd)[last - *i + 1] = 1;
			else
				(*hd)[last - *i + 1] = (*hd)[last - *i + 1] + 1;
			tmp = (*hd);
			(*hd) = ft_strjoin((*hd), "0");
			free(tmp);
		}
		else
		{
			tmp = (*hd);
			(*hd) = ft_strjoin((*hd), "1");
			free(tmp);
		}
	}
}

char	*update_heredoc_name(char *hd)
{
	struct stat	buf;
	int			last;
	int			i;

	if (!hd)
		return (NULL);
	while (stat(hd, &buf) >= 0)
	{
		i = 0;
		last = ft_strlen(hd) - 1;
		increment_filename(&hd, last, &i);
	}
	return (hd);
}
