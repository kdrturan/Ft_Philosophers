/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:42:39 by abturan           #+#    #+#             */
/*   Updated: 2025/05/24 15:36:45 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define PHILO_COUNT_MAX 200
#define PHILO_COUNT_MIN 1
#define ARGUMENT_ERROR "Invalid input."

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef enum e_error_code
{
	PHILO_COUNT_UNDERFLOW,
	PHILO_COUNT_OVERFLOW,
	INT_OVERFLOW
} t_error_code;

typedef struct s_philo t_philo;

typedef struct s_args
{
	t_philo *philos;
	int error;
	int is_finished;
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int how_much_eat;
	long start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t died_mutex;
} t_args;

typedef struct s_philo
{
	int id;
	int meals_eaten;
	long last_meal_time;
	int is_finished;
	t_args *args;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_t thread;
} t_philo;

long get_current_millis(void);
long ft_atoi(const char *str);
void take_forks(t_philo *philo);
void eat_sleep(t_args *args, t_philo *philo);
int check_died(t_args *args, t_philo *philo);
t_args set_args(int ac, char **av);
void ft_usleep(long time);
int print_action(t_philo *philo, const char *msg);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *check_arguments(int ac, char **av);
void set_philos(t_args *args, t_philo *philos, int i);
void *try_to_live_alone(void *data);
void initalize(t_args *args, t_philo *philos);
void *monitor_philos(void *data);
void *philo_jobs(void *data);
void one_philo(t_args *args, t_philo *philos);

#endif