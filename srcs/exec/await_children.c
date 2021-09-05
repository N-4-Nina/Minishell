/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:29:13 by chpl              #+#    #+#             */
/*   Updated: 2021/09/05 18:55:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "signals.h"
#include "utils.h"

void	display_signal_error(int status)
{
	if (status == 139)
		display_error("Segmentation fault (core dumped)\n", "", "");
	else if (status == 131 || status == 134 || status == 136)
		display_error("Nsh: Quit (core dumped)\n", "", "");
}

void	await_child(int *status)
{
	waitpid(-1, status, WUNTRACED);
	if (g_sig_catcher[0] && g_sig_catcher[1] != 3)
		set_sig_status(status);
	else if (WIFSIGNALED(*status))
		display_signal_error(*status);
	else
		*status = *status >> 8;
}

void	await_children(t_sh *nsh, t_cmd *cmd)
{
	int	status;

	cmd->i = 0;
	status = 0;
	while (cmd->i++ < cmd->smpnb)
	{
		waitpid(-1, &status, WUNTRACED);
		if (g_sig_catcher[0] && g_sig_catcher[1] != 3)
			set_sig_status(nsh->last_status);
		else if (WIFSIGNALED(status) && WTERMSIG(status) == 13)
			continue ;
		else if (WIFSIGNALED(status))
			display_signal_error(status);
		else
			*nsh->last_status = status >> 8;
	}
}
