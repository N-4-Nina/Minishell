#include "../../includes/nsh.h"

int	nsh_echo(t_sh *nsh, char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	(void)nsh;
	if (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n')
		{
			n = 0;
			i++;
		}
		while (args[i] != NULL)
		{
			write(1, args[i], ft_strlen(args[i]));
			write(1, " ", 1);
			i++;
		}
	}
	if (n)
		write(1, "\n", 1);
	*(nsh->last_status) = 0; 
	return (0);
}
