/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:23:55 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/14 17:24:43 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned	int	i;
	unsigned	int	dest_count;
	unsigned	int	src_count;

	dest_count = ft_strlen(dest);
	src_count = ft_strlen(src);
	if (size < 1)
		return (src_count);
	if (size < dest_count)
		return (src_count + size);
	i = 0;
	while (src[i] && i + dest_count < size - 1)
	{
		dest[dest_count + i] = src[i];
		i++;
	}
	dest[dest_count + i] = '\0';
	return (dest_count + src_count);
}
