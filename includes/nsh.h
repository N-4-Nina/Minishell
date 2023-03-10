/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:40:11 by chpl              #+#    #+#             */
/*   Updated: 2021/08/28 10:01:23 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NSH_H
# define NSH_H

# include "structures.h"

int		nsh_init(t_sh *nsh, char **envp);
int		nsh_loop(t_sh *nsh);
void	nsh_reset(t_sh *nsh);
int		nsh_clear(t_sh *nsh);

#endif