/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:41:54 by abturan           #+#    #+#             */
/*   Updated: 2025/05/24 15:50:24 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;
	//char	*error = 0;

	//error = check_arguments(ac, av);
	//if (ft_strncmp(error, "", 1))
	//{
	//	printf("%s\n", error);
		//return (1);
	//}
	args = set_args(ac, av);
	philos = malloc(args.number_of_philosophers * sizeof(t_philo));
	args.philos = philos;
	if (philos == NULL || args.error == 1)
	{
		printf("Malloc Error.");
		return (1);
	}
	if (args.number_of_philosophers == 1)
		try_to_live_alone(&args, philos);
	else
		initalize(&args, philos);
	free(args.forks);
	return (0);
}
