/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:42:00 by abturan           #+#    #+#             */
/*   Updated: 2025/05/24 16:13:19 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	set_args(int ac, char **av)
{
	t_args	args;
	int		i;

	i = 0;
	args.number_of_philosophers = ft_atoi(av[1]);
	args.time_to_die = ft_atoi(av[2]);
	args.time_to_eat = ft_atoi(av[3]);
	args.time_to_sleep = ft_atoi(av[4]);
	args.is_finished = 0;
	if (ac == 6)
		args.how_much_eat = ft_atoi(av[5]);
	else
		args.how_much_eat = -1;
	args.forks = malloc(args.number_of_philosophers * sizeof(pthread_mutex_t));
	if (args.forks == NULL)
	{
		args.error = 1;
		return (args);
	}
	pthread_mutex_init(&args.print_mutex, NULL);
	pthread_mutex_init(&args.died_mutex, NULL);
	while (i < args.number_of_philosophers)
		pthread_mutex_init(&args.forks[i++], NULL);
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

long	ft_atoi(const char *str)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		++i;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num = num + (str[i] - '0');
		++i;
		if (num > INT_MAX)
			break ;
	}
	return (num * sign);
}
