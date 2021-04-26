/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:40:11 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 15:35:40 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NSH_H
# define NSH_H

#include <curses.h>
#include <errno.h>  
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>

#include <signal.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <term.h>
#include <X11/keysym.h>

#include "astree.h"
#include "environment.h"
#include "exec.h"
#include "builtins.h"
#include "colors.h"
#include "history.h"
#include "inputs.h"
#include "lexer.h"
#include "token.h"
#include "get_next_line.h"
#include "../libft/libft.h"

#define UP		'A'
#define DOWN	'B'
#define RIGHT	'C'
#define LEFT	'D'

typedef	struct	s_sh
{
	t_ast	*ast;
	t_lex	*lex;
	t_env	*env;
	t_bui	*bui;
	t_inp	*inp;
	t_cmd	*cmd;
}				t_sh;

int build_exec(t_sh *nsh);

int get_input(t_sh *inp);
int handleArrow(char *c);

void display_prompt(t_env *env, t_inp *inp);
int	nsh_loop(t_sh *nsh);
void	nsh_reset(t_sh *nsh);
void	nsh_clear(t_sh *nsh);

char	*get_current_dir_name(void);

int     tree_init(t_sh *nsh);
int		parse(t_sh *nsh);
void	free_tokens(char **tokens);

void    write_dot(t_ast **node);
/* 
*utils.c
*/

int		isBlank(char c);
int		isSpec(char c);
int		isQuote(char c);

int		term_init(void);
void	env_init(t_env **env);

void	set_sig_behav(void);
void	signal_callback_handler(int signum);

#endif
