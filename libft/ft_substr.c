/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:01:55 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/14 15:56:58 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char		*empty_alloc(void)
{
	char *p;

	if (!(p = (char *)malloc(sizeof(char))))
		return (NULL);
	p[0] = '\0';
	return (p);
}

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstring;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (empty_alloc());
	if (!(newstring = malloc(len + 1 * sizeof(char))))
		return (NULL);
	while (s[start + i] && i < len)
	{
		newstring[i] = s[start + i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
