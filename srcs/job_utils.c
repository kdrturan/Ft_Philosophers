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
    ft_usleep(args->time_to_eat * 1000);
    philo->last_meal_time = get_current_millis();
    if (args->how_much_eat != -1)
        philo->meals_eaten++;
    pthread_mutex_unlock(&args->forks[left]);
    pthread_mutex_unlock(&args->forks[right]);
    print_action(philo, "is sleeping");
    ft_usleep(args->time_to_sleep * 1000);
}


int	check_died(t_args *args,t_philo *philo)
{
	if (args->time_to_die > (get_current_millis() - philo->last_meal_time))
	{
    	print_action(philo, "died");
		return (1);
	}
	return (0);
}




t_philo* initalize_variable(void *data, int* left, int* right)
{
	t_philo*	philo;
	
    philo = (t_philo *)data;
	*right = (philo->id + 1) % philo->args->number_of_philosophers;
    *left = philo->id;
    philo->args = philo->args;
	return (philo);
}