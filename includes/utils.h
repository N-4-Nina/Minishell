/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:39:36 by chpl              #+#    #+#             */
/*   Updated: 2021/08/27 15:23:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		isBlank(char c);
int		isSpec(char c);
int		isQuote(char c);
char	*get_current_dir_name(void);
int     display_error(char *one, char *two, char *three);

#endif