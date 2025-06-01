/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:01:22 by abonifac          #+#    #+#             */
/*   Updated: 2025/06/01 23:55:56 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_routine(void *arg)
{
	t_philo		*philo;
	t_params	*p;

	philo = (t_philo *)arg;
	p = philo->params;
	wait_for_start(p);
	print_action(p, philo, P_THINKING);
	if (philo->id % 2 == 0)
		ft_usleep(p->time_to_e * 1000, p);
	while (!get_bool_mutex(&p->table_mutex, &p->end))
	{
		eat(philo);
		print_action(p, philo, P_SLEEPING);
		ft_usleep(p->time_to_s * 1000, p);
		think(philo, p);
	}
	return (NULL);
}

void	think(t_philo *philo, t_params *params)
{
	long	time_to_sleep;

	time_to_sleep = 0;
	print_action(params, philo, P_THINKING);
	if (params->nb_philos % 2 == 1)
	{
		ft_usleep(100, params);
		if (params->time_to_s < params->time_to_e)
		{
			time_to_sleep = (params->time_to_e - params->time_to_s) * 1000;
			ft_usleep(time_to_sleep, params);
		}
	}
}

static void	unlock_mutexes_helper(t_philo *philo)
{
	mutex_unlock_safe(&philo->f_fork->m_fork);
	mutex_unlock_safe(&philo->s_fork->m_fork);
}

void	eat(t_philo *philo)
{
	t_params	*p;

	p = philo->params;
	if (get_bool_mutex(&p->table_mutex, &p->end))
		return ;
	if (get_bool_mutex(&p->table_mutex, &p->end))
	{
		unlock_mutexes_helper(philo);
		return ;
	}
	print_action(p, philo, P_FFORK_TAKEN);
	print_action(p, philo, P_SFORK_TAKEN);
	set_long_mutex(&p->table_mutex, &philo->last_eat_time, print_time(p));
	if (!get_bool_mutex(&p->table_mutex, &p->end))
	{
		print_action(p, philo, P_EATING);
		philo->eat_count++;
		ft_usleep(p->time_to_e * 1000, p);
	}
	if (p->limit_meals != -1 && philo->eat_count >= p->limit_meals)
		set_bool_mutex(&philo->philo_mutex, &philo->is_full, true);
	unlock_mutexes_helper(philo);
}

/*
 * to avoid all philosopher printing at the same time ?
*/
void	print_action(t_params *p, t_philo *philo, t_philo_action action)
{
	mutex_lock_safe(&p->print_mutex);
	if (action == P_DEAD || get_bool_mutex(&p->table_mutex, &p->end) == true)
	{
		if (action == P_DEAD)
		{
			printf(RED BOLD"%ld %d died\n"RESET, print_time(p), philo->id);
			set_bool_mutex(&p->table_mutex, &p->end, true);
			mutex_unlock_safe(&p->print_mutex);
		}
		else
			mutex_unlock_safe(&p->print_mutex);
		return ;
	}
	if (get_bool_mutex(&p->table_mutex, &p->end) == true)
		return ;
	if (action == P_EATING)
		printf("%ld %d is"GREEN " eating\n"RESET, print_time(p), philo->id);
	else if (action == P_SLEEPING)
		printf("%ld %d is"BLUE" sleeping\n"RESET, print_time(p), philo->id);
	else if (action == P_THINKING)
		printf("%ld %d is"PURP " thinking\n"RESET, print_time(p), philo->id);
	else if (action == P_FFORK_TAKEN || action == P_SFORK_TAKEN)
		printf("%ld %d has taken a fork\n", print_time(p), philo->id);
	mutex_unlock_safe(&p->print_mutex);
}
