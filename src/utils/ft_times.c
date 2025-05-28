/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_times.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:19:54 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/28 17:43:17 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_time(t_params *params)
{
	long now;
	
	now = ft_gettimeofday(MSEC) - params->start_time;
	printf("%.8ld ", now);
}

/*
 * Exemple: time_to_d = 1000 = time in ms
 * start_time = 666
 * ft_gettimeofday() = 700
 * ft_gettimeofday() - start_time = 34
 * usleep(200) = 0.2 ms
 * ft_gettimeofday() - statr_time =~ 234
*/

void	ft_usleep(long time_in_us, t_params *params)
{
	long	start_time;

	start_time = ft_gettimeofday(USEC);
	while (ft_gettimeofday(USEC) - start_time < time_in_us)
	{
		if (get_bool_mutex(&params->table_mutex, &params->end) == true)
			return;
		usleep(200);
	}
}