#include "philo.h"


void print_action(t_philo *philo, const char *msg) 
{
    pthread_mutex_lock(&philo->args->print_mutex);
    printf("%lu %d %s\n", (get_current_millis() - philo->args->start_time), philo->id, msg);
    pthread_mutex_unlock(&philo->args->print_mutex);
}


void*    philo_jobs(void *data)
{
    t_philo *philo;
    t_args *args;
    int left;
    int right;
    int flag;

    philo = initalize_variable(data, &left, &right);
    args = philo->args;
    while (1)
    {
        print_action(philo, "is thinking");
        take_forks(args,philo,left,right);
        flag = check_died(args,philo);
        if (flag == 1)
            break;
        eat_sleep(args,philo,left,right);
        if (philo->meals_eaten == args->how_much_eat)
            break;
    }
    return philo;
}


void initalize(t_args *args, t_philo *philos)
{
    int i;

    i = 0;
    args->start_time = get_current_millis();
    while (i < args->number_of_philosophers)
    {    
        philos[i].id = i;
        philos[i].args = args;
        philos[i].meals_eaten = 0;
        philos[i].last_meal_time = get_current_millis();
        pthread_create(&philos[i].thread, NULL, philo_jobs, &philos[i]);
        i++;
    }
    i = 0;
    while (i < args->number_of_philosophers)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
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
    initalize(&args, philos);
    return (0);
}
