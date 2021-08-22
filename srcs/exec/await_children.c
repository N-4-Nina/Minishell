/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:29:13 by chpl              #+#    #+#             */
/*   Updated: 2021/08/22 08:38:17 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structures.h"
#include "../../includes/libs.h"
#include "../../includes/signals.h"

void	await_child(int *status)
{
	waitpid(-1, status, WUNTRACED);
	if (WIFSIGNALED(*status) && *status == 139)
		printf("Segmentation fault (core dumped)\n");
	else if (g_sig_catcher[0])
		set_sig_status(status);
	else
		*status = *status >> 8;
}

void	await_children(t_sh *nsh, t_cmd *cmd)
{
	int	segflt;

	cmd->i = 0;
	segflt = 0;
	while (cmd->i++ < cmd->smpnb)
	{
		waitpid(-1, nsh->last_status, WUNTRACED);
		if (WIFSIGNALED(*nsh->last_status) && *nsh->last_status == 139)
			segflt = 1;
		else if (g_sig_catcher[0])
			set_sig_status(nsh->last_status);
		else
			*nsh->last_status = *nsh->last_status >> 8;
	}
	if (segflt)
		printf("Segmentation fault (core dumped)\n");
}
