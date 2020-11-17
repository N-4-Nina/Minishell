/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:40:11 by chpl              #+#    #+#             */
/*   Updated: 2020/11/17 20:50:06 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NSH_H
# define NSH_H

#include <unistd.h>
#include "get_next_line.h"
#include "../libft/libft.h"

int	nsh_cd(char **args);
int	nsh_exit(char **args);
int	get_next_line(int fd, char **line);

#endif
