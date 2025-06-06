/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:53:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/05 18:55:47 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
* for odds:
* time_to_die -> max(3 * time_to_eat, time_to_eat + time_to_sleep)
* if [time to sleep < (2 * time to eat)] -> 3 * time to eat
* else time_to_die -> time_to_eat + time_to_sleep
* 
* for evens:
* time_to_die -> max (2 * time to eat, time to eat + time to sleep)
* always pick the bigger anyway
* ./philo nb_philo | die | eat | sleep | meals
*/

void	free_threads(t_params *p, int i_fail, bool clean_threads)
{
	int	i;

	i = 0;
	while (i < i_fail && clean_threads == true)
	{
		thread_detach_safe(&p->philos[i].thread_id);
		i++;
	}
	i = 0;
	while (i < p->nb_philos)
	{
		mutex_destroy_safe(&p->forks[i].m_fork);
		i++;
	}
	mutex_destroy_safe(&p->table_mutex);
}

int	init_threads_philos(t_params *p)
{
	int	i;
	int	status;

	status = NO_ERR;
	i = 0;
	while (i < p->nb_philos)
	{
		status = thread_create_safe(&p->philos[i].thread_id,
				dinner_routine, &p->philos[i]);
		if (status == ERROR)
		{
			free_threads(p, i, true);
			return (ERROR);
		}
		i++;
	}
	return (NO_ERR);
}

int	dinner_init(t_params *params)
{
	int	i;
	int	status;

	i = 0;
	status = NO_ERR;
	if (params->nb_philos == 1)
		return (init_thread_one_philo(params));
	params->start_time = ft_gettimeofday(MSEC);
	set_bool_mutex(&params->table_mutex, &params->rdy_to_start, true);
	status = init_threads_philos(params);
	if (status == ERROR)
		return (ERROR);
	status = thread_create_safe(&params->death, end_checker, params);
	if (status == ERROR)
	{
		free_threads(params, params->nb_philos, true);
		return (ERROR);
	}
	i = -1;
	while (++i < params->nb_philos)
		thread_join_safe(&params->philos[i].thread_id);
	thread_join_safe(&params->death);
	free_threads(params, params->nb_philos, false);
	return (NO_ERR);
}

int	main(int ac, char **av)
{
	t_params		params;
	static t_philo	philos[MAX_PHILOS];
	static t_fork	forks[MAX_PHILOS];

	if (check_args(ac, av) == ERROR)
		return (1);
	params.philos = philos;
	params.forks = forks;
	if (init_params(&params, av) == ERROR)
		return (2);
	if (init_forks(&params) == ERROR)
		return (3);
	if (init_philos(&params) == ERROR)
		return (4);
	if (dinner_init(&params) == ERROR)
		return (5);
	return (0);
}
