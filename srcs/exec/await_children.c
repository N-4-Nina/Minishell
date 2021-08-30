/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:29:13 by chpl              #+#    #+#             */
/*   Updated: 2021/08/30 16:57:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structures.h"
#include "../../includes/libs.h"
#include "../../includes/signals.h"
#include "../../includes/utils.h"

void	await_child(int *status)
{
	waitpid(-1, status, WUNTRACED);
	if (WIFSIGNALED(*status) && *status == 139)
		display_error("Segmentation fault (core dumped)\n", "", "");
	else if (g_sig_catcher[0])
		set_sig_status(status);
	else
		*status = *status >> 8;
}

void	await_children(t_sh *nsh, t_cmd *cmd)
{
	int	segflt;
	int	status;

	cmd->i = 0;
	segflt = 0;
	status = 0;
	while (cmd->i++ < cmd->smpnb)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WIFSIGNALED(status) && status == 139)
			segflt = 1;
		else if (WIFSIGNALED(status) && WTERMSIG(status) == 13)
			continue ;
		else if (g_sig_catcher[0])
			set_sig_status(nsh->last_status);
		else
			*nsh->last_status = status >> 8;
	}
	if (segflt)
		display_error("Segmentation fault (core dumped)\n", "", "");
}
