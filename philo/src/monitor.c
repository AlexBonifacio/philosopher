/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:23:10 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/06 17:02:31 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	death_checker(long now_us, t_params *p)
{
	int		i;
	long	last;
	long	limit_us;

	limit_us = p->time_to_d / 1000;
	i = 0;
	while (i < p->nb_philos)
	{
		mutex_lock_safe(&p->table_mutex);
		last = p->philos[i].last_eat_time;
		mutex_unlock_safe(&p->table_mutex);
		if (now_us - last >= limit_us)
		{
			set_bool_mutex(&p->table_mutex, &p->end, true);
			print_action(p, &p->philos[i], P_DEAD);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	meal_checker(t_params *param)
{
	int	fulls;
	int	i;

	fulls = 0;
	i = 0;
	mutex_lock_safe(&param->table_mutex);
	if (param->limit_meals > 0)
	{
		while (i < param->nb_philos)
		{
			if (param->philos[i].eat_count >= param->limit_meals)
				fulls++;
			i++;
		}
		if (fulls == param->nb_philos)
		{
			param->end = true;
			mutex_unlock_safe(&param->table_mutex);
			return (true);
		}
	}
	mutex_unlock_safe(&param->table_mutex);
	return (false);
}

void	*end_checker(void *arg)
{
	t_params	*param;
	long		now;

	param = (t_params *)arg;
	wait_for_start(param);
	while (true)
	{
		if (get_bool_mutex(&param->table_mutex, &param->end))
			break ;
		now = print_time(param);
		if (death_checker(now, param) == true)
			return (NULL);
		if (meal_checker(param) == true)
			return (NULL);
		ft_usleep(200, param);
	}
	return (NULL);
}
