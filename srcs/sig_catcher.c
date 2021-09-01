/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_catcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:18:21 by user42            #+#    #+#             */
/*   Updated: 2021/09/01 07:50:09 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	set_sig_status(int *status)
{
	*status = 128 + g_sig_catcher[1];
	reset_sig_catcher();
}

void	catch_signal(int signum)
{
	g_sig_catcher[0] = 1;
	g_sig_catcher[1] = signum;
}
