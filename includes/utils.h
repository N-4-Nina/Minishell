/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:39:36 by chpl              #+#    #+#             */
/*   Updated: 2021/09/01 08:23:33 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		is_blank(char c);
int		is_spec(char c);
int		is_quote(char c);
char	*get_current_dir_name(void);
int		display_error(char *one, char *two, char *three);

#endif