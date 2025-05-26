/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:58:57 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/26 17:38:39 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int mutex_safe_call(t_mutex *mutex)
// {
// 	if (pthread_mutex_lock(mutex) != 0)
// 	{
// 		return ft_exit("failed to lock mutex");
// 	}
// 	if (pthread_mutex_unlock(mutex) != 0)
// 	{
// 		return ft_exit("failed to unlock mutex");
// 	}
// 	if (pthread_mutex_destroy(mutex) != 0)
// 	{
// 		return ft_exit("failed to destroy mutex");
// 	}
// 	if (pthread_mutex_init(mutex, NULL) != 0)
// 	{
// 		return ft_exit("failed to initialize mutex");
// 	}
// 	return 0;
// }

int	mutex_init_safe(t_mutex *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return ft_exit("failed to initialize mutex");
	return NO_ERR;
}

int	mutex_destroy_safe(t_mutex *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
		return ft_exit("failed to destroy mutex");
	return NO_ERR;
}

int thread_create_safe(pthread_t *thread, void *(*func)(void*), void *arg)
{
	if (pthread_create(thread, NULL, func, arg) != 0)
	{
		return ft_exit("failed to create thread");
	}
	return NO_ERR;
}

int thread_safe_call(pthread_t *thread)
{
	if (pthread_join(*thread, NULL) != 0)
	{
		return ft_exit("failed to join thread");
	}
	if (pthread_detach(*thread) != 0)
	{
		return ft_exit("failed to detach thread");
	}
	return 0;
}