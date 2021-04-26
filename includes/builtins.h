#ifndef BUILTINS_H
# define BUILTINS_H

#include "nsh.h"

typedef struct  s_sh t_sh;
typedef int (bi_func) (t_sh *nsh, char **args);

typedef	struct	s_builtins
{
	char	*str[7];
    bi_func *func[7];
}               t_bui;

int	is_builtin(char *s, t_bui b);

int	nsh_echo(t_sh *nsh, char **args);
int	nsh_cd(t_sh *nsh, char **args);
int	nsh_pwd(t_sh *nsh, char **args);
int	nsh_export(t_sh *nsh, char **args);
int	nsh_unset(t_sh *nsh, char **args);
int	nsh_env(t_sh *nsh, char **args);
int	nsh_exit(t_sh *nsh, char **args);


#endif