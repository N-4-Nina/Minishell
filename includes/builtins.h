/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:44:33 by user42            #+#    #+#             */
/*   Updated: 2021/09/19 10:13:52 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structures.h"

void	bui_init(t_sh *nsh);
int		is_builtin(char *s, t_bui *b);
int		nsh_echo(t_sh *nsh, char **args);
int		nsh_cd(t_sh *nsh, char **args);
int		nsh_pwd(t_sh *nsh, char **args);
int		nsh_export(t_sh *nsh, char **args);
int		nsh_export_env(t_sh *nsh);
int		nsh_unset(t_sh *nsh, char **args);
int		nsh_mute_unset(t_sh *nsh, char **args);
int		nsh_env(t_sh *nsh, char **args);
int		nsh_exit(t_sh *nsh, char **args);

#endif