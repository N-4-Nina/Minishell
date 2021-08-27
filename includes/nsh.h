/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:40:11 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 10:31:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NSH_H
# define NSH_H

# include "structures.h"

int		nsh_init(t_sh *nsh, char **envp);
int		nsh_loop(t_sh *nsh);
void	nsh_reset(t_sh *nsh);
void	nsh_clear(t_sh *nsh);

#endif