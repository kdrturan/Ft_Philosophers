#include "philo.h"


int	ft_isdigit(int ch)
{
	return (ch >= '0' && ch <= '9');
}

char*	check_arguments(int ac, char **av)
{
	int i;
	
	if (ac != 5 && ac != 6)
		return ("ARGUMENT ERROR");
	while (av[--ac] && ac > 0)
	{
		i = 0;
		while (av[ac][i])
			if (!ft_isdigit(av[ac][i++]))
				return ("ARGUMENT ERROR");
	}
	return ("");
}
