#ifndef BUILTINS_H
# define BUILTINS_H

# include "structures.h"

void	bui_init(t_sh *nsh);
int		is_builtin(char *s, t_bui *b);
int		nsh_echo(t_sh *nsh, char **args);
int		nsh_cd(t_sh *nsh, char **args);
int		nsh_pwd(t_sh *nsh, char **args);
int		nsh_export(t_sh *nsh, char **args);
int		nsh_unset(t_sh *nsh, char **args);
int		nsh_env(t_sh *nsh, char **args);
int		nsh_exit(t_sh *nsh, char **args);

#endif