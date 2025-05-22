#include "philo.h"

long get_current_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}



void ft_usleep(long time)
{
	long	start;

	start = get_current_millis();
	while (get_current_millis() - start < time)
		usleep(500);
}