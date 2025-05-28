/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:24:45 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/28 22:56:50 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_nb_of_args(int ac)
{

	if (ac != 5 && ac != 6)
	{
		printf(RED BOLD "Error: " RESET "Wrong number of arguments\n" BLUE BOLD "Usage: " RESET
						"./philo number_of_philosophers time_to_die "
						"time_to_eat time_to_sleep "
						"[number_of_times_each_philosopher_must_eat]\n" RESET);
		return ERROR;
	}
	return NO_ERR;
}

static int check_digit(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		if (!av[i] || ft_strlen(av[i]) == 0)
			return ft_error("Arguments cannot be NULL or empty");
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && (av[i][j] != '-' && av[i][j] != '+' && !ft_isspace(av[i][j])))
				return ft_error("Arguments must be digits");
			j++;
		}
		i++;
	}
	return NO_ERR;
}

int check_args(int ac, char **av)
{

	if (check_nb_of_args(ac) == 0)
		return ERROR;
	if (check_digit(av) == 0)
		return ERROR;
	return NO_ERR;
}