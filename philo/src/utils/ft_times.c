/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_times.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:19:54 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/06 16:42:29 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	print_time(t_params *params)
{
	long	now;

	now = ft_gettimeofday(MSEC) - params->start_time;
	return (now);
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
	long	start;
	long	target;
	long	now;

	start = ft_gettimeofday(USEC);
	target = time_in_us + start;
	if (time_in_us > 12000)
	{
		usleep(time_in_us - 10000);
	}
	while (true)
	{
		now = ft_gettimeofday(USEC);
		if (now >= target)
			break ;
		if (get_bool_mutex(&params->table_mutex, &params->end) == true)
			return ;
		usleep(100);
	}
}
