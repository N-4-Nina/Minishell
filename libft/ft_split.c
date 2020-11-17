/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:59:23 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/14 16:54:28 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *str, char c)
{
	int i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if ((!i && (str[i] != c)) ||
			(i > 0 && (str[i - 1] == c) && (str[i] != c)))
			words++;
		i++;
	}
	return (words);
}

static	int		string_length(char *str, int i, char c)
{
	int length;

	length = 0;
	while (str[i] && (str[i] != c))
	{
		i++;
		length++;
	}
	return (length);
}

static	char	**fill_array(char **array, char *str, char c)
{
	int	i;
	int	j;
	int	k;
	int	length;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && (str[i] != c))
		{
			length = string_length(str, i, c);
			array[j] = (char *)malloc(length + 1);
			while (str[i] && (str[i] != c))
				array[j][k++] = str[i++];
			array[j][k] = '\0';
			array[++j] = NULL;
		}
	}
	return (array);
}

static	char	**empty_array(void)
{
	char		**res;

	res = (char **)malloc(sizeof(char *));
	res[0] = NULL;
	return (res);
}

char			**ft_split(char const *s, char c)
{
	char	**split;
	char	*str;
	int		words;

	str = (char *)s;
	split = NULL;
	if (!str || !str[0])
		return (empty_array());
	words = count_words(str, c);
	if (!words)
		return (empty_array());
	if (!(split = malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	split[words] = NULL;
	split = fill_array(split, str, c);
	return (split);
}
