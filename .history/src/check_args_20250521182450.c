/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:24:45 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/21 18:24:50 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_nb_of_args(int ac)
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

void	check_digit(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf(RED BOLD"Error: "RESET"Arguments must be digits\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

void check_args(int ac, char **av)
{
	check_nb_of_args(ac);
	check_digit(av);
}