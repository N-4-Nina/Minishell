/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:13:17 by chappelle         #+#    #+#             */
/*   Updated: 2021/09/05 17:12:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "exec.h"

void	recover_origin(int origin[2])
{
	dup2(origin[0], STDIN_FILENO);
	dup2(origin[1], STDOUT_FILENO);
	close(origin[0]);
	close(origin[1]);
}

void	redirect(t_smpl *s, int *ori_in, int *ori_out)
{
	*ori_in = dup(STDIN_FILENO);
	*ori_out = dup(STDOUT_FILENO);
	if (s->input != -1 && s->input != -1 && s->input != STDIN_FILENO)
		dup2(s->input, STDIN_FILENO);
	if (s->output != -1 && s->output != -1 && s->output != STDOUT_FILENO)
		dup2(s->output, STDOUT_FILENO);
}
