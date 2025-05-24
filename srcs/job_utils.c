/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:41:41 by abturan           #+#    #+#             */
/*   Updated: 2025/05/24 15:37:22 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");
	}
}

void	eat_sleep(t_args *args, t_philo *philo)
{
	print_action(philo, "is eating");
	ft_usleep(args->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&args->died_mutex);
	philo->last_meal_time = get_current_millis();
	if (args->how_much_eat != -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&args->died_mutex);
	print_action(philo, "is sleeping");
	ft_usleep(args->time_to_sleep);
}

int	check_died(t_args *args, t_philo *philo)
{
	pthread_mutex_lock(&args->died_mutex);
	if (args->is_finished == 1 || args->how_much_eat == philo->meals_eaten)
	{
		pthread_mutex_unlock(&args->died_mutex);
		return (1);
	}
	if ((get_current_millis() - philo->last_meal_time) > args->time_to_die)
	{
		pthread_mutex_unlock(&args->died_mutex);
		if (args->is_finished == 0)
		{
			print_action(philo, "died");
			pthread_mutex_lock(&args->print_mutex);
			args->is_finished = 1;
			pthread_mutex_unlock(&args->print_mutex);
		}
		return (1);
	}
	pthread_mutex_unlock(&args->died_mutex);
	return (0);
}

void	set_philos(t_args *args, t_philo *philos, int i)
{
	philos[i].id = i;
	philos[i].args = args;
	philos[i].meals_eaten = 0;
	philos[i].is_finished = 0;
	if (i == args->number_of_philosophers)
	{
		philos[i].l_fork = &args->forks[i];
		philos[i].r_fork = &args->forks[0];
	}
	else
	{
		philos[i].l_fork = &args->forks[i];
		philos[i].r_fork = &args->forks[i + 1];
	}
	philos[i].last_meal_time = get_current_millis();
}
