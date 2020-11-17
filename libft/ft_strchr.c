/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:35:13 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/05 16:32:40 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	tofind;
	char	*ptr;

	i = 0;
	ptr = (char*)s;
	tofind = (char)c;
	while (s[i])
	{
		if (s[i] == tofind)
			return (ptr);
		i++;
		ptr++;
	}
	if (s[i] == tofind)
		return (ptr);
	return (NULL);
}
