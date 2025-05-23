/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:53:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/23 18:46:30 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * number_of_philosophers time_to_die time_to_eat time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
*/

void init_params(t_params *params, char **av)
{
	(void)params;
	(void)av;
	// int i = 0;

	params->nb_philos = ft_atol(av[1]);
	params->time_to_d = ft_atol(av[2]) * 1000;
	params->time_to_e = ft_atol(av[3]) * 1000;
	params->time_to_s = ft_atol(av[4]) * 1000;
	if (av[5])
		params->limit_meals = ft_atol(av[5]);
	else
		params->limit_meals = 0;
}

int main(int ac, char **av)
{
	t_params params;
	check_args(ac, av);
	init_params(&params, av);
	printf("nb_philos: %u\n", params.nb_philos);
	printf("time_to_d: %ld\n", params.time_to_d);
	printf("time_to_e: %ld\n", params.time_to_e);
	printf("time_to_s: %ld\n", params.time_to_s);
	
	(void)av;
	return (0);
}
