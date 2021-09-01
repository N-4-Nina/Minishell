/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:27:00 by chpl              #+#    #+#             */
/*   Updated: 2021/09/01 08:13:19 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

int	g_sig_catcher[2];

void	reset_sig_catcher(void);
void	set_sig_status(int *status);
void	set_sig_behav(int mode, char *cmd);
void	catch_signal(int signum);
#endif