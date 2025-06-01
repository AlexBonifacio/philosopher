/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:23:10 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/01 22:23:21 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool death_checker(long now, t_params *param)
{
	int i;

	i = 0;
	while (i < param->nb_philos)
	{
		if (now - param->philos[i].last_eat_time > param->time_to_d)
		{
			param->end = true;
			mutex_unlock_safe(&param->table_mutex);
			print_action(param, &param->philos[i], P_DEAD);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool meal_checker(t_params *param)
{
	int fulls;
	int i;

	fulls=0;
	i = 0;
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
			return true;
		}
	}
	return (false);
}

void *end_checker(void *arg)
{
	t_params *param;
	long now;
	
	param = (t_params *)arg;
	wait_for_start(param);
	while (!param->end)
	{
		now = print_time(param);
		mutex_lock_safe(&param->table_mutex);
		if (death_checker(now, param) == true)
			return NULL;
		if (meal_checker(param) == true)
			return NULL;
		mutex_unlock_safe(&param->table_mutex);
		ft_usleep(500, param);
	}
	return arg;
}