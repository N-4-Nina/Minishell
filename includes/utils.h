/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:39:36 by chpl              #+#    #+#             */
/*   Updated: 2021/08/10 16:49:23 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_array(char **ar, int size);
int		isBlank(char c);
int		isSpec(char c);
int		isQuote(char c);
char	*get_current_dir_name(void);

#endif