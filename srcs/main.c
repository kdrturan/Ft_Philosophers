#include "philo.h"


void print_action(t_philo *philo, const char *msg) {
    pthread_mutex_lock(&philo->args->print_mutex);
    printf("%lu %d %s\n", (get_current_millis() - philo->args->start_time), philo->id, msg);
    pthread_mutex_unlock(&philo->args->print_mutex);
}


void*    philo_jobs(void *data)
{
    t_philo *philo = (t_philo *)data;
    t_args *args = philo->args;
    int left = philo->id;
    int right = (philo->id + 1) % args->number_of_philosophers;

    while (1)
    {
        // if (args->time_to_die > (get_current_millis() - philo->last_meal_time))
        // {
        //     break;
        // }
        
        print_action(philo, "is thinking");

        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(&args->forks[right]);
            pthread_mutex_lock(&args->forks[left]);
        }
        else
        {
            pthread_mutex_lock(&args->forks[left]);
            pthread_mutex_lock(&args->forks[right]);
        }


        print_action(philo, "is eating");
        philo->last_meal_time = get_current_millis();
        usleep(args->time_to_eat * 1000);

        pthread_mutex_unlock(&args->forks[left]);
        pthread_mutex_unlock(&args->forks[right]);



        print_action(philo, "is sleeping");
        usleep(args->time_to_sleep * 1000);
    }
    printf("--%d\n",philo->id);

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
    printf("%d\n",philos[i].id);
    // i = 0;
    // while (i < args->number_of_philosophers)
    // {
    //     pthread_join(philos[i].thread, NULL);
        
    //     pthread_detach(philos[i].thread);
    // }
    i = 0;
    while (i < args->number_of_philosophers)
    {
        pthread_join(philos[i].thread, NULL);
    }
     
}


int main(int ac, char **av)
{
    t_args  args;
    t_philo* philos;
    int i;
    if (ac < 0)
        return (0);
    i = 0;
    args.number_of_philosophers = ft_atoi(av[1]);
    args.time_to_die = ft_atoi(av[2]);
    args.time_to_eat = ft_atoi(av[3]);
    args.time_to_sleep = ft_atoi(av[4]);

    philos = malloc(args.number_of_philosophers * sizeof(t_philo));
    pthread_mutex_init(&args.print_mutex, NULL);

    while (i < args.number_of_philosophers)
        pthread_mutex_init(&args.forks[i++], NULL);
    initalize(&args, philos);
    

    //check_errors(ac, av);
}
