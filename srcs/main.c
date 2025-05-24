#include "philo.h"


void print_action(t_philo *philo, const char *msg) 
{
    pthread_mutex_lock(&philo->args->print_mutex);
    if (philo->args->is_finished == 0)
    {
        printf("%lu %d %s\n", (get_current_millis() - philo->args->start_time), philo->id, msg);
    }
    pthread_mutex_unlock(&philo->args->print_mutex);
}


void*    philo_jobs(void *data)
{
    t_philo *philo;
    t_args *args;
    int left;
    int right;


    philo = initalize_variable(data, &left, &right);
    args = philo->args;
    while (1)
    {
        print_action(philo, "is thinking");
        take_forks(philo);
        eat_sleep(args,philo);
        if (args->is_finished)
            break;
        if (philo->meals_eaten == args->how_much_eat)
            break;
    }
    return philo;
}

void* monitor_philos(void *data)
{
	t_args *args = (t_args *)data;
	int i;

	while (1)
	{
		i = 0;

		while (i < args->number_of_philosophers )
		{    
            if (args->is_finished)
                return NULL;
			if (check_died(args, &args->philos[i]))
				return NULL;
			i++;
		}
	}
    return NULL;
}



void initalize(t_args *args, t_philo *philos)
{
    pthread_t monitor;
    int i;

    i = 0;
    args->start_time = get_current_millis();
    while (i < args->number_of_philosophers)
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
    pthread_join(monitor,NULL);
}

int main(int ac, char **av)
{
    t_args  args;
    t_philo* philos;
    char*   error;

    error = check_arguments(ac,av);
    if (ft_strncmp(error,"",1))
    {
        printf("%s\n",error);
        return (-1);
    }
    args = set_args(ac,av);
    philos = malloc(args.number_of_philosophers * sizeof(t_philo));
    args.philos = philos;
    initalize(&args, philos);
    free(args.forks);
    return (0);
}
