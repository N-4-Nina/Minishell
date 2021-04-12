#ifndef BUILTINS_H
# define BUILTINS_H

int	nsh_echo(t_env *env, char **args);
int	nsh_cd(t_env *env, char **args);
int	nsh_pwd(t_env *env, char **args);
int	nsh_export(t_env *env, char **args);
int	nsh_unset(t_env *env, char **args);
int	nsh_env(t_env *env, char **args);
int	nsh_exit(t_env *env, char **args);

typedef	struct	s_builtins
{
	char	*builtin_str[7];
    int     (*builtin_func[7]) (char **);
}               t_bui;


#endif