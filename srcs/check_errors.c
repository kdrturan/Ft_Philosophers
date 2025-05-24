/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:41:46 by abturan           #+#    #+#             */
/*   Updated: 2025/05/24 15:48:41 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int ch)
{
	return (ch >= '0' && ch <= '9');
}

char	*check_arguments(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return ("ARGUMENT ERROR-");
	while (av[--ac] && ac > 0)
	{
		i = 0;
		while (av[ac][i])
			if (!ft_isdigit(av[ac][i++]))
				return ("-ARGUMENT ERROR");
	}
	return ("");
}
