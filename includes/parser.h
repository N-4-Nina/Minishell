/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:31:08 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 11:51:07 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int	parse_word(t_sh *nsh, t_ast **current);
int	parse_io_file(t_sh *nsh, t_ast **current);
int	parse_simple_cmd(t_sh *nsh, t_ast **current);
int	parse_pipe_seq(t_sh *nsh, t_ast **current, int dir);
int	parse_command(t_sh *nsh, t_ast **current);
int	validate(t_lex *l, t_ttype expected);
int	syntax_error(t_tok t);

#endif