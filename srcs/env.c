/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:37:25 by chpl              #+#    #+#             */
/*   Updated: 2020/11/26 10:11:49 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nsh.h"

int	strmatch(char *s1, char *s2)
{
	size_t	len;

	len = ft_strlen(s1);
	if (ft_strlen(s2) > len)
		len = ft_strlen(s2);
	if (ft_strncmp(s1, s2, len) == 0)
		return (1);
	return (0);
}

char	**env_to_array(void)
{
	char	**arr;
	int	i;
	int	j;
	t_env	*list;

	list = *g_env;
	i = 0;
	arr = (char**)malloc(sizeof(char*));
	while (list)
	{
		j = 0;
		arr[i] = malloc(ft_strlen(list->name) + ft_strlen(list->value) +2);
		while(list->name[j])
		{
			arr[i][j] = list->name[j];
			j++;
		}
		arr[i][j] = '=';
		j = 0;
		while(list->value[j])
		{
			arr[i][j+1+ft_strlen(list->name)] = list->value[j];
			j++;
		}
		i++;
		list = list->next;
	}
	return (arr);
}

void	add_var(char *name, char *value)
{
	t_env	*list;
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	list = *g_env;
	if (list == NULL)
		*g_env = new;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

t_env	*find_by_name(char *str)
{
	t_env	*current;

	current = *g_env;
	while(current)
	{
		if (strmatch(str, current->name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	env_init()
{
	char	*cdn;

	g_env = (t_env**)malloc(sizeof(t_env*));
	cdn = get_current_dir_name(); 
	add_var("PWD", cdn);
	free(cdn);
	add_var("PATH", "/bin/");
	//add_var("USER", execve("/usr/bin/id", ["id", "-u", "-n"], NULL));

}

