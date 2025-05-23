#include "philo.h"

void	take_forks(t_args *args,t_philo *philo, int left, int right)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&args->forks[right]);
        print_action(philo, " has taken a fork");
        pthread_mutex_lock(&args->forks[left]);
        print_action(philo, " has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&args->forks[left]);
        print_action(philo, " has taken a fork");
        pthread_mutex_lock(&args->forks[right]);
        print_action(philo, " has taken a fork");
    }	
}

void	eat_sleep(t_args *args,t_philo *philo, int left, int right)
{
    print_action(philo, "is eating");
    ft_usleep(args->time_to_eat);
	pthread_mutex_lock(&args->died_mutex);
    philo->last_meal_time = get_current_millis();
	pthread_mutex_unlock(&args->died_mutex);
    if (args->how_much_eat != -1)
	philo->meals_eaten++;
    pthread_mutex_unlock(&args->forks[left]);
    pthread_mutex_unlock(&args->forks[right]);
    print_action(philo, "is sleeping");
    ft_usleep(args->time_to_sleep);
}


int	check_died(t_args *args, t_philo *philo)
{
	if (args->is_finished == 1 || args->how_much_eat == philo->meals_eaten)
		return (1);
	pthread_mutex_lock(&args->died_mutex);
	if ((get_current_millis() - philo->last_meal_time) > args->time_to_die)
	{
		pthread_mutex_unlock(&args->died_mutex);
		if (args->is_finished == 0)
		{
			print_action(philo,"died");
			pthread_mutex_lock(&args->print_mutex);
			args->is_finished = 1;    
			pthread_mutex_unlock(&args->print_mutex);
		}
		return (1);
	}
	pthread_mutex_unlock(&args->died_mutex);
	return (0);
}




t_philo* initalize_variable(void *data, int* left, int* right)
{
	t_philo*	philo;
	
    philo = (t_philo *)data;
	*right = (philo->id + 1) % philo->args->number_of_philosophers;
    *left = philo->id;
	return (philo);
}