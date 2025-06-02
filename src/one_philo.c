/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:07:17 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/02 16:04:24 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo(void *arg)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)arg;
	params = philo->params;
	params->start_time = ft_gettimeofday(MSEC);
	print_action(params, philo, P_FFORK_TAKEN);
	ft_usleep(params->time_to_d, params);
	print_action(params, philo, P_DEAD);
	set_bool_mutex(&params->table_mutex, &params->end, true);
	return (NULL);
}

int	init_thread_one_philo(t_params *params)
{
	int	status;

	status = thread_create_safe(&params->philos[0].thread_id,
			one_philo, &params->philos[0]);
	if (status == ERROR)
	{
		mutex_destroy_safe(&params->table_mutex);
		mutex_destroy_safe(&params->forks[0].m_fork);
		return (ERROR);
	}
	thread_join_safe(&params->philos[0].thread_id);
	mutex_destroy_safe(&params->table_mutex);
	mutex_destroy_safe(&params->forks[0].m_fork);
	return (NO_ERR);
}
