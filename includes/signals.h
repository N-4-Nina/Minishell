/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:27:00 by chpl              #+#    #+#             */
/*   Updated: 2021/08/31 12:21:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

int	g_sig_catcher[2];

void	reset_sig_catcher(void);
void	set_sig_status(int *status);
void	set_sig_behav(int mode);
void	catch_signal(int signum);
#endif