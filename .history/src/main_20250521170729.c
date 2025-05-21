/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:53:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/21 17:07:29 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * number_of_philosophers time_to_die time_to_eat time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
*/
void check_args(int ac); 

int main(int ac, char **av)
{
	// t_params params;
	check_args(ac);
	printf("%d\n", FORK);
	(void)av;
	return (0);
}

void check_args(int ac)
{
	if (ac != 5 || ac != 6)
	{
		printf(RED BOLD"Error: Wrong number of arguments\n"
		GREEN "Usage: ./philo number_of_philosophers time_to_die "
		"time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		exit(EXIT_FAILURE);
	}
}