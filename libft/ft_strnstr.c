/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:55:41 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/07 14:53:02 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	char	*ptr;
	char	*haystackcopy;

	i = 0;
	haystackcopy = (char*)haystack;
	if (!(needle[0]))
		return (haystackcopy);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (!(needle[j + 1]))
			{
				ptr = &haystackcopy[i];
				return (ptr);
			}
			j++;
		}
		i++;
	}
	return (0);
}
