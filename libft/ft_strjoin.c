/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:22:19 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/14 16:07:30 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i[2];
	char		*newstring;

	i[0] = 0;
	i[1] = 0;
	if (!s1 && !s2)
		return (NULL);
	newstring = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstring)
		return (NULL);
	while (i[0] < ft_strlen(s1))
	{
		newstring[i[1]] = s1[i[0]];
		i[0]++;
		i[1]++;
	}
	i[0] = 0;
	while (i[0] < ft_strlen(s2))
	{
		newstring[i[1]] = s2[i[0]];
		i[0]++;
		i[1]++;
	}
	newstring[i[1]] = '\0';
	return (newstring);
}
