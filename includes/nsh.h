/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:40:11 by chpl              #+#    #+#             */
/*   Updated: 2021/08/07 12:10:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NSH_H
# define NSH_H

#include <curses.h>
#include <errno.h>  
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <term.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


#include "astree.h"
#include "environment.h"
#include "builtins.h"
#include "colors.h"
#include "inputs.h"
#include "lexer.h"
#include "token.h"
#include "termc.h"
#include "get_next_line.h"
#include "../libft/libft.h"

#define FLAGS_LESS		O_RDONLY
#define FLAGS_GREAT		O_CREAT | O_WRONLY | O_TRUNC
#define FLAGS_DGREAT	O_CREAT | O_WRONLY | O_APPEND
#define FLAGS_DLESS		-1

#define INTERACTIVE		1
#define RESET			2
#define CATCH			3
#define HEREDOC			4

int	g_sig_catcher[2];

typedef	struct	s_sh
{
	t_ast	*ast;
	t_lex	*lex;
	t_env	*env;
	t_bui	*bui;
	t_inp	*inp;
	int		*last_status;
	struct	s_cmd	*cmd;
	struct	termios	*term;
}				t_sh;

#include "exec.h"

int		nsh_init(t_sh *nsh);
int     here_doc(t_smpl *s, char *hd, char *end);
void	reset_sig_catcher(void);
void	set_sig_status(int *status);

int build_exec(t_sh *nsh, t_ast *node);

int get_input(t_sh *inp);
int handleArrow(char *c);

void build_prompt(t_env *env, t_inp *inp);
int	nsh_loop(t_sh *nsh);
void	nsh_reset(t_sh *nsh);
void	nsh_clear(t_sh *nsh);

char	*get_current_dir_name(void);

int     tree_init(t_sh *nsh);
int		parse(t_sh *nsh);
void	free_tokens(char **tokens);

void    write_dot(t_ast **node);

//expansion
char    *expand_word(char *s, t_env *env, int *status);

int		strmatch(char *s1, char *s2);

int		g_status(int set, int val);
/* 
*utils.c
*/
void    free_array(char **ar, int size);


int		isBlank(char c);
int		isSpec(char c);
int		isQuote(char c);

void	env_init(t_env **env);

void	set_sig_behav(int mode);
void	signal_callback_handler(int signum);

#endif
