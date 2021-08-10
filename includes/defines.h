/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 12:00:04 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 16:46:51 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define FLAGS_LESS		O_RDONLY
# define FLAGS_GREAT    577
# define FLAGS_DGREAT   1089
# define FLAGS_DLESS		-1
# define INTERACTIVE		1
# define RESET			2
# define CATCH			3
# define HEREDOC			4
# define HD_CATCH		5
# define SET_BOLD    "\033[1m"
# define SET_LIGHT    "\033[0m"
# define SET_RED     "\x1b[31m"
# define SET_GREEN   "\x1b[32m"
# define SET_YELLOW  "\x1b[33m"
# define SET_BLUE    "\x1b[34m"
# define SET_WHITE   "\x1b[0m"
# define	COLOR_SIZE	6
# define BOLD_SIZE   5
# define AST_LEFT 0
# define AST_RIGHT 1

#endif