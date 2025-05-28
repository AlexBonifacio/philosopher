/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:39:54 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/28 22:56:50 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int thread_create_safe(pthread_t *thread, void *(*func)(void *), void *arg)
{
	if (pthread_create(thread, NULL, func, arg) != 0)
		return ft_error("failed to create thread");
	return NO_ERR;
}

int thread_join_safe(pthread_t *thread)
{
	if (pthread_join(*thread, NULL) != 0)
		return ft_error("failed to join thread");
	return NO_ERR;
}

int thread_detach_safe(pthread_t *thread)
{
	if (pthread_detach(*thread) != 0)
		return ft_error("failed to detach thread");
	return NO_ERR;
}
