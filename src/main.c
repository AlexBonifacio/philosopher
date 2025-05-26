/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:53:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/26 23:00:44 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * number_of_philosophers time_to_die time_to_eat time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
 */

int check_eq_zero(t_params *params)
{
	if (params->nb_philos == 0 ||
		params->time_to_d == 0 || params->time_to_e == 0 ||
		params->time_to_s == 0 || params->limit_meals == 0)
	{
		return ERROR;
	}
	else
	{
		return NO_ERR;
	}
}
int init_params(t_params *params, char **av)
{

	params->nb_philos = ft_atol(av[1]);
	if (params->nb_philos > MAX_PHILOS)
		return ft_exit("Too many philosophers, max is 200");
	params->time_to_d = ft_atol(av[2]);
	params->time_to_e = ft_atol(av[3]);
	params->time_to_s = ft_atol(av[4]);
	if (av[5])
		params->limit_meals = ft_atol(av[5]);
	else
		params->limit_meals = -1;
	if (check_eq_zero(params) == 0)
		return ERROR;
	params->start_time = 0;
	params->end = false;
	return NO_ERR;
}

int init_mutex(t_params *params)
{
	int i;
	int status;

	i = 0;
	status = NO_ERR;
	while (i < params->nb_philos)
	{
		status = mutex_init_safe(&params->forks[i].m_fork);
		if (status == ERROR)
			break;
		params->forks[i].id = i + 1;
		i++;
	}
	if (status == ERROR)
	{
		while (--i >= 0)
			mutex_destroy_safe(&params->forks[i].m_fork);
	}
	return status;
}

void *dinner_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	return philo;
}

int dinner_init(t_params *params)
{
	int i;
	int	status;
	
	i = 0;
	status = NO_ERR;
	if (params->nb_philos == 1)
		return NO_ERR; //
	else
	{
		while (i < params->nb_philos)
		{
			status = thread_create_safe(&params->philos[i].thread_id, dinner_routine, &params->philos[i]);
			if (status == ERROR)
				break;
			i++;
		}
		if (status == ERROR)
		{
			while (--i >= 0)
				pthread_detach(params->philos[i].thread_id);
			while (++i < params->nb_philos)
				mutex_destroy_safe(&params->forks[i].m_fork);
			return status;
		}
	}
	return NO_ERR;
}

/*
 * (0 + 5 - 1) % 5 = 4
 * (1 + 5 - 1) % 5 = 0
 * On odd 135 philosophers, the first fork is the one on the left,
 * On even 24 philosophers, the first fork is the one on the right.
 */
void init_philos(t_params *params)
{
	int i;
	int nb_philos = params->nb_philos;

	i = 0;
	while (i < params->nb_philos)
	{
		params->philos[i].id = i + 1;
		params->philos[i].eat_count = 0;
		params->philos[i].is_full = false;
		params->philos[i].f_fork = &params->forks[i];
		params->philos[i].s_fork = &params->forks[(i + nb_philos - 1) % nb_philos];
		if (params->philos[i].id % 2 == 0)
		{
			params->philos[i].f_fork = &params->forks[(i + nb_philos - 1) % nb_philos];
			params->philos[i].s_fork = &params->forks[i];
		}
		params->forks[i].id = i;
		params->philos[i].last_eat_time = 0;
		params->philos[i].params = params;
		i++;
	}
}

int main(int ac, char **av)
{
	t_params params;
	static t_philo philos[MAX_PHILOS];
	static t_fork forks[MAX_PHILOS];

	if (check_args(ac, av) == ERROR)
		return 1;
	params.philos = philos;
	params.forks = forks;
	if (init_params(&params, av) == ERROR)
		return 2;
	if (init_mutex(&params) == ERROR)
		return 3;
	init_philos(&params);
	ft_gettimeofday();

	return (0);
}
