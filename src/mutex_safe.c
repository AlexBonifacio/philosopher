/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:58:57 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/01 23:44:46 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init_safe(t_mutex *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		return (ft_error("failed to initialize mutex"));
	return (NO_ERR);
}

int	mutex_destroy_safe(t_mutex *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
		return (ft_error("failed to destroy mutex"));
	return (NO_ERR);
}

int	mutex_lock_safe(t_mutex *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (ft_error("failed to lock mutex"));
	return (NO_ERR);
}

int	mutex_unlock_safe(t_mutex *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_error("failed to unlock mutex"));
	return (NO_ERR);
}
