/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:40:11 by chpl              #+#    #+#             */
/*   Updated: 2020/11/25 15:35:40 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NSH_H
# define NSH_H

#include <unistd.h>
#include <linux/limits.h>
#include "get_next_line.h"
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

#define SET_RED     "\x1b[31m"
#define SET_GREEN   "\x1b[32m"
#define SET_YELLOW  "\x1b[33m"
#define SET_BLUE    "\x1b[34m"
#define SET_MAGENTA "\x1b[35m"
#define SET_CYAN    "\x1b[36m"
#define SET_WHITE   "\x1b[0m"

typedef	struct	s_env
{
	char	*name;
	char	*value;
	struct	s_env	*next;
}		t_env;

extern	t_env	**g_env;


int	nsh_echo(char **args);
int	nsh_cd(char **args);
int	nsh_pwd(char **args);
int	nsh_export(char **args);
int	nsh_unset(char **args);
int	nsh_env(char **args);
int	nsh_exit(char **args);
int	get_next_line(int fd, char **line);

char	*get_current_dir_name(void);

t_env	*find_by_name(char *str);

void	add_var(char *name, char *value);
void	env_init(void);
char	**env_to_array(void);

#endif
