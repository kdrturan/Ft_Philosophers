#include "philo.h"



t_args	set_args(int ac,char **av)
{
	t_args args;
    int i;

    i = 0;
	args.number_of_philosophers = ft_atoi(av[1]);
    args.time_to_die = ft_atoi(av[2]);
    args.time_to_eat = ft_atoi(av[3]);
    args.time_to_sleep = ft_atoi(av[4]);
	args.is_finished = 0;
	if (ac == 6)
        args.how_much_eat = ft_atoi(av[5]);
    else
	{
        args.how_much_eat = -1;
	}
	args.forks = malloc(args.number_of_philosophers * sizeof(pthread_mutex_t));
	pthread_mutex_init(&args.print_mutex, NULL);
	pthread_mutex_init(&args.died_mutex, NULL);
    while (i < args.number_of_philosophers)
	{
        pthread_mutex_init(&args.forks[i++], NULL);
	}
	return (args);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}