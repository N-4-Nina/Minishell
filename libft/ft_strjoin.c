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
	size_t		i;
	size_t		j;
	char		*newstring;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!(newstring = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (i < ft_strlen(s1))
	{
		newstring[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		newstring[j] = s2[i];
		i++;
		j++;
	}
	newstring[j] = '\0';
	return (newstring);
}
