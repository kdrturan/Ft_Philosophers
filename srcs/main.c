/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:41:54 by abturan           #+#    #+#             */
/*   Updated: 2025/05/24 16:21:19 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;
	char	*error;

	philos = NULL;
	error = 0;
	error = check_arguments(ac, av);
	if (ft_strncmp(error, "", 1))
		return (printf("%s\n", error), 1);
	args = set_args(ac, av);
	philos = malloc(args.number_of_philosophers * sizeof(t_philo));
	args.philos = philos;
	if (args.number_of_philosophers == 1)
		return (one_philo(&args, philos), 1);
	if (philos == NULL || args.error == 1)
		return (printf("Malloc Error."), 1);
	initalize(&args, philos);
	free(args.forks);
	return (0);
}
