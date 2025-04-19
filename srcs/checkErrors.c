#include "philo.h"

void	check_errors(int ac, char **av)
{
	long	num;
	
	if (ac != 5 && ac != 6)
		handle_error(ARGUMENT_ERROR);
	while (av[--ac] && ac > 0)
	{
		num = ft_atoi(av[ac]);
		if (ac == 1 || ac == 5)
		{
			if (ac == 5 && (num < 0 || num > INT_MAX))
				handle_error(ARGUMENT_ERROR);
			if (ac == 1 && num < PHILO_COUNT_MIN)
				handle_error(PHILO_COUNT_UNDERFLOW);
			if (ac == 1 && num > PHILO_COUNT_MAX)
				handle_error(PHILO_COUNT_OVERFLOW);
		}
		if (num < 1 || num > INT_MAX)
			handle_error(ARGUMENT_ERROR);
	}
}
