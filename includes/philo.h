#ifndef PHILO_H
# define PHILO_H

# define PHILO_COUNT_MAX 200
# define PHILO_COUNT_MIN 1

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

typedef enum	e_error_code
{
	ARGUMENT_ERROR,
	PHILO_COUNT_UNDERFLOW,
	PHILO_COUNT_OVERFLOW,
	INT_OVERFLOW
}				t_error_code;

typedef struct	s_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	long start_time;
	pthread_mutex_t forks[200];
    pthread_mutex_t print_mutex;
}				t_args;


typedef struct	s_philo
{
	int id;
    int meals_eaten;
    long last_meal_time;
	t_args *args;
	pthread_t thread;
}				t_philo;

void	terminate_prog(char *msg, int exit_code);
void	handle_error(size_t error_code);
void	check_errors(int ac, char **av);
long get_current_millis(void);
long	ft_atoi(const char *str);

#endif