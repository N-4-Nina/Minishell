/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:48:35 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/14 16:20:34 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int end;
	int i;

	if (!s1 || !set)
		return (NULL);
	if (s1[1] == '\0')
		return (ft_calloc(1, sizeof(char)));
	i = 0;
	end = ft_strlen((char *)s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	if (start > end)
		return (ft_calloc(1, sizeof(char)));
	while (ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
