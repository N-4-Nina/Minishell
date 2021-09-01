/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:38:37 by chpl              #+#    #+#             */
/*   Updated: 2021/09/01 09:17:44 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* note to self -and others-:
 * Not only is the lexer different from parser,
 * but it comes before it and enables it.
 * Building a lexer supie we tokenize the input string,
 * specifying a type for each token. 
 * -Lexer distinguish between tokens, stores them,
 * and for each one answers the question:
 * "what is it ?" wheareas
 * -Parser, knowing what is what and obeying 
 * a defined grammar answers the question:
 * "can this type of token be here ?"
 * 
 * The Lexer should also probably check if some quotes 
 * are still open at the end of the command
 */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/lexer.h"
#include "../includes/utils.h"
#include "../includes/lexer.h"

void	copy_data(t_lex *l)
{
	l->t[l->j].data = (char *)malloc(l->t[l->j].len + 1);
	if (!l->t[l->j].data)
		return (abort_token(l));
	ft_strlcpy(l->t[l->j].data, &l->inp[l->i], l->t[l->j].len + 1);
}

int	check_multiline(t_lex *l)
{
	int	len;

	len = ft_strlen(l->inp);
	if (len)
	{
		if (len > 1 && l->inp[len - 1] == '\\' && l->inp[len - 2] == '\\')
			return (0);
		else if (l->inp[len - 1] == '\\')
		{
			display_error("Multiline is not supported.\n", "", "");
			return (1);
		}
	}
	return (0);
}

int	set_spec_type(t_lex *l)
{
	static char	*types[6] = {">>", ">", "<<", "<", "|", ";"};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (!(ft_strncmp(l->t[l->j].data, types[i], 3)))
			return (l->t[l->j].type = i);
		i++;
	}
	return (-1);
}

int	tokenize(t_lex *l)
{
	l->i = 0;
	l->j = 0;
	while (l->i < l->inp_size && l->j < l->nt)
	{
		token_init(&l->t[l->j]);
		if (is_blank(l->inp[l->i]))
			handle_blank(l);
		else if (is_spec(l->inp[l->i]))
			handle_spec(l);
		else if (!is_spec(l->inp[l->i]))
			handle_word(l);
	}
	return (1);
}

int	lex_build(t_lex *l, char *prompt)
{
	if (!l->inp)
		return (0);
	l->inp_size = ft_strlen(l->inp);
	if (check_multiline(l) || count_tokens(l) <= 0)
	{
		free(prompt);
		free(l->inp);
		return (0);
	}
	l->t = malloc(sizeof(t_tok) * l->nt);
	if (!l->t)
	{
		free(prompt);
		free(l->inp);
		return (0);
	}
	tokenize(l);
	l->i = 0;
	return (l->nt);
}
