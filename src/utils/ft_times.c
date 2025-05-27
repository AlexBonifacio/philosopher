/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_times.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:19:54 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/27 22:35:33 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_time(t_params *params)
{
	long time;
	
	if (params->end)
		return;
	set_long_mutex(&params->table_mutex, &time, ft_gettimeofday() - params->start_time);
	// Check dead?
	printf("%.8ld\n", time);
}

void	ft_usleep(long time_in_ms)
{
	long	start_time;

	start_time = ft_gettimeofday();
	while (ft_gettimeofday() - start_time < time_in_ms)
	{
		usleep(100);
	}
}