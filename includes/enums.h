/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:35:02 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 16:47:57 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_token_type
{
	DGREAT,
	GREAT,
	DLESS,
	LESS,
	PIPE,
	SEMI,
	WORD,
}					t_ttype;

typedef enum e_node_type
{
	N_PROGRAM = 0,
	N_CMD,
	N_CMD_SUFFIX,
	N_IO_FILE,
	N_PIPE_SEQ,
	N_SIMPLE_CMD,
	N_WORD,
	N_RED
}					t_ntype;

#endif