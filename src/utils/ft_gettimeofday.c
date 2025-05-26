/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettimeofday.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:59:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/26 16:56:38 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
struct timeval {
	time_t      tv_sec;      seconds 
	suseconds_t tv_usec;     microseconds 
};
*/

long ft_gettimeofday(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (gettimeofday(&time, NULL) != 0)
		ft_exit("gettimeofday failed");
	long start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	// sleep(1);
	// gettimeofday(&time, NULL);
	// long elap_time = time.tv_sec * 1000 + time.tv_usec / 1000 - start_time;
	printf("timeoday %08ld\n", start_time);
	return(start_time);
}