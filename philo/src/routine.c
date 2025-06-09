/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:01:22 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/09 22:32:32 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_routine(void *arg)
{
	t_philo		*philo;
	t_params	*p;
	long		sleep;

	philo = (t_philo *)arg;
	p = philo->params;
	sleep = p->time_to_s;
	wait_for_start(p);
	// if (get_long_mutex(&p->table_mutex, &p->start_time) == -1)
	// 	set_long_mutex(&p->table_mutex, &p->start_time, ft_gettimeofday(MSEC));
	set_long_mutex(&p->table_mutex, &philo->last_eat_time, 0);
	print_action(p, philo, P_THINKING);
	if (philo->id % 2 == 0)
		ft_usleep(p->time_to_e, p);
	while (!get_bool_mutex(&p->table_mutex, &p->end))
	{
		eat(philo);
		print_action(p, philo, P_SLEEPING);
		ft_usleep(sleep, p);
		think(philo, p);
	}
	return (NULL);
}

void	think(t_philo *philo, t_params *params)
{
	long	time_to_sleep;

	time_to_sleep = (params->time_to_e - params->time_to_s);
	print_action(params, philo, P_THINKING);
	if (params->nb_philos % 2 == 1)
	{
		ft_usleep(200, params);
		if (params->time_to_s < params->time_to_e)
		{
			ft_usleep(time_to_sleep, params);
		}
	}
}

static void	unlock_mutexes_helper(t_philo *philo)
{
	mutex_unlock_safe(&philo->f_fork->m_fork);
	mutex_unlock_safe(&philo->s_fork->m_fork);
}

void	eat(t_philo *phi)
{
	t_params	*p;

	p = phi->params;
	if (get_bool_mutex(&p->table_mutex, &p->end))
		return ;
	mutex_lock_safe(&phi->f_fork->m_fork);
	mutex_lock_safe(&phi->s_fork->m_fork);
	if (get_bool_mutex(&p->table_mutex, &p->end))
	{
		unlock_mutexes_helper(phi);
		return ;
	}
	print_action(p, phi, P_FFORK_TAKEN);
	print_action(p, phi, P_SFORK_TAKEN);
	set_long_mutex(&p->table_mutex, &phi->last_eat_time, print_time(p));
	if (!get_bool_mutex(&p->table_mutex, &p->end))
	{
		print_action(p, phi, P_EATING);
		set_long_mutex(&p->table_mutex, &phi->eat_count, phi->eat_count + 1);
	}
	ft_usleep(p->time_to_e, p);
	if (p->limit_meals != -1 && phi->eat_count >= p->limit_meals)
		set_bool_mutex(&phi->philo_mutex, &phi->is_full, true);
	unlock_mutexes_helper(phi);
}

void	print_action(t_params *p, t_philo *philo, t_philo_action action)
{
	long	time;

	time = print_time(p);
	mutex_lock_safe(&p->print_mutex);
	if (action == P_DEAD || get_bool_mutex(&p->table_mutex, &p->end) == true)
	{
		if (action == P_DEAD)
		{
			printf(RED BOLD"%ld %d died\n"RESET, time, philo->id);
			set_bool_mutex(&p->table_mutex, &p->end, true);
		}
		mutex_unlock_safe(&p->print_mutex);
		return ;
	}
	if (action == P_EATING)
		printf("%ld %d is"GREEN " eating\n"RESET, time, philo->id);
	else if (action == P_SLEEPING)
		printf("%ld %d is"BLUE" sleeping\n"RESET, time, philo->id);
	else if (action == P_THINKING)
		printf("%ld %d is"PURP " thinking\n"RESET, time, philo->id);
	else if (action == P_FFORK_TAKEN || action == P_SFORK_TAKEN)
		printf("%ld %d has taken a fork\n", time, philo->id);
	mutex_unlock_safe(&p->print_mutex);
}
