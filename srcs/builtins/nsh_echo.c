#include "../../includes/nsh.h"

int	nsh_echo(t_sh *nsh, char **args)
{
	int	i;

	i = 1;
	(void)nsh;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}