/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:36:55 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/02 16:04:06 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * (0 + 5 - 1) % 5 = 4
 * (1 + 5 - 1) % 5 = 0
 * On odd 135 philosophers, the first fork is the one on the left,
 * On even 24 philosophers, the first fork is the one on the right.
 */

int	init_philos(t_params *p)
{
	int	i;

	i = -1;
	while (++i < p->nb_philos)
	{
		p->philos[i].id = i + 1;
		p->philos[i].eat_count = 0;
		p->philos[i].is_full = false;
		p->philos[i].f_fork = &p->forks[i];
		p->philos[i].s_fork = &p->forks[(i + p->nb_philos - 1) % p->nb_philos];
		if (p->philos[i].id % 2 == 0)
		{
			p->philos[i].f_fork = &p->forks[(i + p->nb_philos - 1)
				% p->nb_philos];
			p->philos[i].s_fork = &p->forks[i];
		}
		if (mutex_init_safe(&p->philos[i].philo_mutex) == ERROR)
		{
			while (--i >= 0)
				mutex_destroy_safe(&p->philos[i].philo_mutex);
			return (ERROR);
		}
		p->philos[i].params = p;
	}
	return (NO_ERR);
}

static void	basic_params(t_params *params, char **av)
{
	params->time_to_d = ft_atol(av[2]) * 1000;
	params->time_to_e = ft_atol(av[3]) * 1000;
	params->time_to_s = ft_atol(av[4]) * 1000;
	if (av[5])
		params->limit_meals = ft_atol(av[5]);
	else
		params->limit_meals = -1;
}

int	init_params(t_params *params, char **av)
{
	params->nb_philos = ft_atol(av[1]);
	if (params->nb_philos > MAX_PHILOS)
	{
		printf(RED BOLD"Error: "RESET
			"Too many philosophers, max is %d\n", MAX_PHILOS);
		return (ERROR);
	}
	basic_params(params, av);
	if (check_eq_zero(params) == 0)
		return (ERROR);
	if (mutex_init_safe(&params->table_mutex) == ERROR)
		return (ERROR);
	if (mutex_init_safe(&params->print_mutex) == ERROR)
	{
		mutex_destroy_safe(&params->table_mutex);
		return (ERROR);
	}
	params->start_time = 0;
	params->end = false;
	params->rdy_to_start = false;
	return (NO_ERR);
}

int	init_forks(t_params *params)
{
	int	i;
	int	status;

	i = 0;
	status = NO_ERR;
	while (i < params->nb_philos)
	{
		status = mutex_init_safe(&params->forks[i].m_fork);
		i++;
		if (status == ERROR)
			break ;
	}
	if (status == ERROR)
	{
		while (--i >= 0)
			mutex_destroy_safe(&params->forks[i].m_fork);
	}
	return (status);
}
