/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:53:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/21 18:22:08 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * number_of_philosophers time_to_die time_to_eat time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
*/
void check_args(int ac); 

void init_params(t_params *params, char **av)
{
	(void)params;
	(void)av;
	int i = 1;

	while (av[i])
	{
		ft_atol(av[i]);
		i++;
	}
}

int main(int ac, char **av)
{
	t_params params;
	check_args(ac);
	init_params(&params, av);
	printf("%d\n", FORK);
	(void)av;
	return (0);
}
void	check_nb_of_args(ac)
{
	
	if (ac != 5 && ac != 6)
	{
		printf(RED BOLD"Error: "RESET "Wrong number of arguments\n"
			BLUE BOLD"Usage: "RESET
			"./philo number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n"
			RESET);
			exit(EXIT_FAILURE);
	}	
}

void check_args(int ac)
{
	check_nb_of_args(ac);
	check_de
}