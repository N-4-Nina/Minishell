/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:39:36 by chpl              #+#    #+#             */
/*   Updated: 2021/08/26 12:28:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	sort_array(char **ar, int size);
void	free_array(char **ar, int size);
int		isBlank(char c);
int		isSpec(char c);
int		isQuote(char c);
char	*get_current_dir_name(void);

#endif