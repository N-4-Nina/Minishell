/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh_export_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <chpl@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 10:05:01 by chpl              #+#    #+#             */
/*   Updated: 2021/09/19 10:14:15 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libs.h"
#include "environment.h"
#include "builtins.h"
#include "arrays.h"
#include "utils.h"

void	nsh_export_env_write(char *var)
{
	int		j;
	int		size;
	char	*str;

	j = 0;
	size = 17 + ft_strlen(var);
	str = malloc(size);
	ft_strlcpy(str, "declare -x ", 12);
	while (var[j] != '=')
		j++;
	ft_strlcat(str, var, j + 12);
	ft_strlcat(str, "=\"", size);
	j++;
	ft_strlcat(str, &var[j], size);
	ft_strlcat(str, "\"\n", size);
	write(1, str, ft_strlen(str));
	free(str);
}

int	nsh_export_env(t_sh *nsh)
{
	char	**arr;
	int		size;
	int		i;

	i = 0;
	arr = env_to_array(nsh->env, &size);
	sort_array(arr, size);
	while (arr[i])
		nsh_export_env_write(arr[i++]);
	free_array(arr, size);
	*(nsh->last_status) = 0;
	return (0);
}
