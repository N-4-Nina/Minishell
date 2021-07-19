#include "../../includes/nsh.h"

int	is_all_n(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	nsh_echo(t_sh *nsh, char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	if (args[i])
	{
		while (args[i] != NULL)
		{
			if (args[i][0] == '-' && is_all_n(&args[i][1]))
			{
				n = 0;
				i++;
				continue ;
			}
			write(1, args[i], ft_strlen(args[i]));
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (n)
		write(1, "\n", 1);
	*(nsh->last_status) = 0;
	return (0);
}
