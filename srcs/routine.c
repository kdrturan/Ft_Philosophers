/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:35:17 by abturan           #+#    #+#             */
/*   Updated: 2025/05/24 15:39:02 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_jobs(void *data)
{
	t_philo	*philo;
	t_args	*args;
	int		flag;

	philo = (t_philo *)data;
	args = philo->args;
	while (1)
	{
		flag = print_action(philo, "is thinking");
		take_forks(philo);
		eat_sleep(args, philo);
		if (flag)
			break ;
		pthread_mutex_lock(&args->died_mutex);
		if (philo->meals_eaten == args->how_much_eat)
		{
			pthread_mutex_unlock(&args->died_mutex);
			break ;
		}
		pthread_mutex_unlock(&args->died_mutex);
	}
	return (philo);
}

void	*monitor_philos(void *data)
{
	t_args	*args;
	int		i;

	args = (t_args *)data;
	while (1)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			if (args->is_finished)
				return (NULL);
			if (check_died(args, &args->philos[i]))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

void	initalize(t_args *args, t_philo *philos)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	args->start_time = get_current_millis();
	while (i < args->number_of_philosophers)
	{
		set_philos(args, philos, i);
		pthread_create(&philos[i].thread, NULL, philo_jobs, &philos[i]);
		i++;
	}
	i = 0;
	pthread_create(&monitor, NULL, monitor_philos, args);
	while (i < args->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	print_action(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	if (philo->args->is_finished == 0)
	{
		printf("%lu %d %s\n", (get_current_millis() - philo->args->start_time),
			philo->id, msg);
		pthread_mutex_unlock(&philo->args->print_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->print_mutex);
		return (1);
	}
}

void	try_to_live_alone(t_args *args, t_philo *philos)
{
	pthread_t	monitor;

	args->start_time = get_current_millis();
	set_philos(args, philos, 0);
	pthread_create(&philos[0].thread, NULL, philo_jobs, &philos[0]);
	pthread_create(&monitor, NULL, monitor_philos, args);
	pthread_join(philos[0].thread, NULL);
	pthread_join(monitor, NULL);
}
