/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:56:33 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/27 11:27:20 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_long_mutex(t_mutex *mutex, long *dest, long value)
{

	mutex_lock_safe(mutex);
	*dest = value;
	mutex_unlock_safe(mutex);
}

long 	get_long_mutex(t_mutex *mutex, long *value)
{
	long 	result;

	mutex_lock_safe(mutex);
	result = *value;
	mutex_unlock_safe(mutex);
	return result;
}

void set_bool_mutex(t_mutex *mutex, bool *dest, bool value)
{
	mutex_lock_safe(mutex);
	*dest = value;
	mutex_unlock_safe(mutex);
}

bool get_bool_mutex(t_mutex *mutex, bool *value)
{
	bool result;
	
	mutex_lock_safe(mutex);
	result = *value;
	mutex_unlock_safe(mutex);
	return result;
}