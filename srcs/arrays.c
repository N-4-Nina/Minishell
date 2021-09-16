/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 10:53:40 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

int	ft_strcmp(const char *p1, const char *p2)
{
	int	i;

	i = 0;
	while (p1[i] && p2[i] && p1[i] == p2[i])
		i++;
	return (p1[i] - p2[i]);
}

void	sort_array(char **ar, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(ar[i], ar[j]) > 0)
			{
				tmp = ar[j];
				ar[j] = ar[i];
				ar[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	array_size(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

void	free_array(char **ar, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ar[i])
			free(ar[i]);
		i++;
	}
	if (ar)
		free(ar);
}
