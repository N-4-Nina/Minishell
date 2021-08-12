/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:40:53 by chpl              #+#    #+#             */
/*   Updated: 2021/08/12 14:08:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structures.h"
#include "../includes/libs.h"
#include "../includes/astree.h"
#include "../includes/parser.h"

int	syntax_error(t_tok t)
{
	static char	*spec[6] = {">>", ">", "<<", "<", "|", ";"};

	if (t.type == WORD)
		printf("Syntax Error, unexpected token near %s \n", t.data);
	else if (t.type > -1 && t.type < 6)
		printf("Syntax Error, unexpected token near \"%s\" \n", spec[t.type]);
	else
		printf("Syntax Error: couldn't set token type.\n");
	return (0);
}
