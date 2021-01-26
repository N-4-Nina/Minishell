/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 16:28:28 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int	istoken(char c)
{
	return (c == '>' || c == '<' || 
		c == '|' || c == ';' ||
		c == '\'' || c == '"' ||
		c == '\\' || c == '$');
}

int	count_tokens(char *s)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (s[i])
        {
				if (s[i] && isBlank(s[i]))
				{
					while (s[i] && isBlank(s[i]))
						i++;
					count++;
				}
				else if (s[i] && istoken(s[i]))
				{
					if (s[i] == '>' && s[i + 1] == '>')
						i += 2;
					else
						i += 1;
					count++;
				}
                else if (s[i] && !istoken(s[i]))
                {
					while (s[i] && !(isBlank(s[i])) && !(istoken(s[i])))
						i++;
                    count++;
                }
        }
	return (count);
}

char	**empty_array(void)
{
	char	**res;
	res = (char **)malloc(sizeof(char *));
	res[0] = NULL;
	return (res);
}

char	**abort_token(char **tokens, int j)
{
	while (j > 0)
	{
		tokens[j] = NULL;
		free(tokens[j]);
		j--;
	}
	return (empty_array());
}
void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while(tokens[i])
		free(tokens[i++]);
	free(tokens);
}

char    **tokenize(char **array, char *str)
{
        int     i;
        int     j;
        int     k;
        int     length;

        i = 0;
        j = 0;
        while (str[i])
        {
                k = 0;
				length = 0;
				if (str[i] && isBlank(str[i]))
				{
					while (str[i + length] && isBlank(str[i + length]))
						length++;
					if(!(array[j] = (char *)malloc(length + 1)))
							return (abort_token(array, j - 1));
					while (k < length)
						array[j][k++] = str[i++];
					array[j][k] = '\0';
					array[++j] = NULL;
				}
				else if (str[i] && istoken(str[i]))
				{
					if (str[i] == '>' && str[i + 1] == '>')
						length = 2;
					else
						length = 1;
					if(!(array[j] = (char *)malloc(length + 1)))
						return (abort_token(array, j - 1));
					while (k < length)
						array[j][k++] = str[i++];
					array[j][k] = '\0';
					array[++j] = NULL;
				}
                else if (str[i] && !istoken(str[i]))
                {
					while (str[i+length] && !(isBlank(str[i+length])) && !(istoken(str[i+length])))
						length++;
                    if(!(array[j] = (char *)malloc(length + 1)))
						return (abort_token(array, j - 1));
                    while (k < length)
                            array[j][k++] = str[i++];
                     array[j][k] = '\0';
                    array[++j] = NULL;
                }
        }
        return (array);
}

char	**parse(char *s, int *c)
{
	int	count;
	char	**tokens;
	
	if (!s || !s[0])
		return (empty_array());
	count = count_tokens(s);
	if (!count)
		return (empty_array());
	if (!(tokens = malloc(sizeof(char*) * (count + 1))))
        return (NULL);
    tokens[count] = NULL;
    tokens = tokenize(tokens, s);
	*c = count;
    return (tokens);
}
