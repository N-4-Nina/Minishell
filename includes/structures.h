/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:12 by chpl              #+#    #+#             */
/*   Updated: 2021/08/24 20:18:25 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "enums.h"

typedef struct s_sh	t_sh;
typedef int (bi_func) (t_sh *nsh, char **args);

typedef struct s_ast
{
	char			*data;
	int				len;
	t_ntype			type;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_token
{
	int				len;
	t_ttype			type;
	char			*data;
}				t_tok;

typedef struct s_lex
{
	char	*inp;
	t_tok	*t;
	int		inpSize;
	int		syntax_error;
	int		nt;
	int		i;
	int		j;
}				t_lex;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_builtins
{
	char	**str;
	bi_func	*func[7];
}			t_bui;

typedef struct s_inp
{
	char		*line;
	char		*prompt;
}				t_inp;

typedef struct s_simple
{
	int		input;
	int		output;
	char	*heredoc;
	int		hasheredoc;
	int		isbuiltin;
	int		has_cmd_word;
	int		argc;
	int		filesnb;
	int		*files;
	char	*path;
	char	**argv;
}			t_smpl;

typedef struct s_command
{
	int		i;
	int		smpnb;
	int		*red[2];
	int		*ori[2];
	t_smpl	**smpl;
}			t_cmd;

typedef struct s_sh
{
	t_ast			*ast;
	t_lex			*lex;
	t_env			*env;
	t_bui			*bui;
	t_inp			*inp;
	t_cmd			*cmd;
	int				*last_status;
}					t_sh;

#endif