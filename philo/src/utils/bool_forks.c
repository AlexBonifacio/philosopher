/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:20:18 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/10 11:25:28 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_fork *f)
{
	pthread_mutex_lock(&f->m_fork);
	f->is_locked = true;
}

void	unlock_fork(t_fork *f)
{
	f->is_locked = false;
	pthread_mutex_unlock(&f->m_fork);
}
