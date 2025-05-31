/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettimeofday.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:59:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/31 00:41:58 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
struct timeval {
	time_t      tv_sec;      seconds
	suseconds_t tv_usec;     microseconds
};
*/

long ft_gettimeofday(int flag)
{
	struct timeval time;
	long start_time;
	
	start_time = 0;
	if (gettimeofday(&time, NULL) != 0)
		ft_error("gettimeofday failed");
	if (flag == MSEC)
		start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	else if (flag == USEC)
		start_time = time.tv_sec * 1000000 + time.tv_usec;
	return (start_time);
}