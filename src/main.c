/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:53:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/29 00:24:34 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * number_of_philosophers time_to_die time_to_eat time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
 */

int check_eq_zero(t_params *params)
{
	if (params->nb_philos == 0 ||
		params->time_to_d == 0 || params->time_to_e == 0 ||
		params->time_to_s == 0 || params->limit_meals == 0)
	{
		return ERROR;
	}
	else
	{
		return NO_ERR;
	}
}
int init_params(t_params *params, char **av)
{

	params->nb_philos = ft_atol(av[1]);
	if (params->nb_philos > MAX_PHILOS)
	{
		printf(RED BOLD"Error: "RESET "Too many philosophers, max is %d\n", MAX_PHILOS);	
		return ERROR;
	}
	params->time_to_d = ft_atol(av[2]);
	params->time_to_e = ft_atol(av[3]);
	params->time_to_s = ft_atol(av[4]);
	if (av[5])
		params->limit_meals = ft_atol(av[5]);
	else
		params->limit_meals = -1;
	if (check_eq_zero(params) == 0)
		return ERROR;
	mutex_init_safe(&params->print_mutex);
	mutex_init_safe(&params->table_mutex);
	// if (mutex_init_safe(&params->table_mutex) == ERROR || mutex_init_safe(&params->print_mutex) == ERROR)
	// 	return ERROR;
	params->start_time = 0;
	params->end = false;
	params->rdy_to_start = false;
	return NO_ERR;
}

int init_forks(t_params *params)
{
	int i;
	int status;

	i = 0;
	status = NO_ERR;
	while (i < params->nb_philos)
	{
		status = mutex_init_safe(&params->forks[i].m_fork);
		if (status == ERROR)
			break;
		params->forks[i].id = i + 1;
		i++;
	}
	if (status == ERROR)
	{
		while (--i >= 0)
			mutex_destroy_safe(&params->forks[i].m_fork);
	}
	return status;
}

void print_action(t_params *params, t_philo *philo, t_philo_action action)
{
	mutex_lock_safe(&params->print_mutex);
	print_time(params);
	
	// if (get_bool_mutex(&params->table_mutex, &params->end) == true)
	// {
	// 	mutex_unlock_safe(&params->table_mutex);
	// 	return;
	// }
	if ((action == P_EATING))
	{
		printf("Philosopher %d is eating\n", philo->id);
		// ft_usleep(params->time_to_e * 1000, params);
	}
	else if (action == P_SLEEPING)
	{
		printf("Philosopher %d is sleeping\n", philo->id);
		// ft_usleep(params->time_to_s * 1000, params);
	}
	else if (action == P_THINKING)
	{
		printf("Philosopher %d is thinking\n", philo->id);
	}
	else if (action == P_DEAD)
	{
		printf(RED BOLD"Philosopher %d is dead\n"RESET, philo->id);
		set_bool_mutex(&params->table_mutex, &params->end, true);
	}
	else if (action == P_FFORK_TAKEN)
	{
		printf("Philosopher %d has taken a fork\n", philo->id);
	}
	else if (action == P_SFORK_TAKEN)
	{
		printf("Philosopher %d has taken a second fork\n", philo->id);
	}
	mutex_unlock_safe(&params->print_mutex);
}

void eat(t_philo *philo)
{
	t_params *params;

	params = philo->params;
	mutex_lock_safe(&philo->f_fork->m_fork);
	print_action(params, philo, P_FFORK_TAKEN);
	mutex_lock_safe(&philo->s_fork->m_fork);
	print_action(params, philo, P_SFORK_TAKEN);
	set_long_mutex(&params->table_mutex, &philo->last_eat_time, ft_gettimeofday(MSEC));
	print_action(params, philo, P_EATING);
	philo->eat_count++;
	ft_usleep(params->time_to_e * 1000, params);
	if (params->limit_meals != -1 && philo->eat_count >= params->limit_meals)
	{
		philo->is_full = true;
		set_bool_mutex(&params->table_mutex, &params->end, true);
		return;
	}
	mutex_unlock_safe(&philo->f_fork->m_fork);
	mutex_unlock_safe(&philo->s_fork->m_fork);
}

void think(t_philo *philo, t_params *params)
{
	print_action(params, philo, P_THINKING);
	// ft_usleep(50, params);
}
void *dinner_routine(void *params)
{
	t_philo *philo;

	philo = (t_philo *)params;
	wait_for_start(philo->params);
	// printf("Philosopher %d is ready to start\n", philo->id);
	while (get_bool_mutex(&philo->params->table_mutex, &philo->params->end) == false)
	{
		eat(philo);
		print_action(philo->params, philo, P_SLEEPING);
		ft_usleep(philo->params->time_to_s * 1000, params);

				// ft_usleep(philo->params->time_to_s * 1000, philo->params);
		think(philo, philo->params);

	}
	
	// while (get_bool_mutex(&philo->params->table_mutex, &philo->params->end) == false)
	// {
	// 	set_bool_mutex(&philo->params->table_mutex, &philo->params->end, true);
	// }
	return philo;
}

int dinner_init(t_params *params)
{
	int i;
	int	status;
	
	i = 0;
	status = NO_ERR;
	if (params->nb_philos == 1)
		return NO_ERR; //
	else
	{
		while (i < params->nb_philos)
		{
			status = thread_create_safe(&params->philos[i].thread_id, dinner_routine, &params->philos[i]);
			if (status == ERROR)
				break;
			i++;
		}
		if (status == ERROR)
		{
			while (--i >= 0)
				thread_detach_safe(&params->philos[i].thread_id);
			while (++i < params->nb_philos)
				mutex_destroy_safe(&params->forks[i].m_fork);
			return status;
		}
	}
	params->start_time = ft_gettimeofday(MSEC);
	set_bool_mutex(&params->table_mutex, &params->rdy_to_start, true);
	i = 0;
	while (i < params->nb_philos)
	{
		thread_join_safe(&params->philos[i].thread_id);
		i++;
	}
	return NO_ERR;
}

/*
 * (0 + 5 - 1) % 5 = 4
 * (1 + 5 - 1) % 5 = 0
 * On odd 135 philosophers, the first fork is the one on the left,
 * On even 24 philosophers, the first fork is the one on the right.
 */
int init_philos(t_params *params)
{
	int i;
	int nb_philos = params->nb_philos;

	i = 0;
	while (i < params->nb_philos)
	{
		params->philos[i].id = i + 1;
		params->philos[i].eat_count = 0;
		params->philos[i].is_full = false;
		params->philos[i].f_fork = &params->forks[i];
		params->philos[i].s_fork = &params->forks[(i + nb_philos - 1) % nb_philos];
		if (params->philos[i].id % 2 == 0)
		{
			params->philos[i].f_fork = &params->forks[(i + nb_philos - 1) % nb_philos];
			params->philos[i].s_fork = &params->forks[i];
		}
		params->forks[i].id = i;
		params->philos[i].last_eat_time = 0;
		if (mutex_init_safe(&params->philos[i].philo_mutex) == ERROR)
		{
			while (--i >= 0)
				mutex_destroy_safe(&params->philos[i].philo_mutex);
			return ERROR;
		}
		params->philos[i].params = params;
		i++;
	}
	return NO_ERR;
}

int main(int ac, char **av)
{
	t_params params;
	static t_philo philos[MAX_PHILOS];
	static t_fork forks[MAX_PHILOS];

	if (check_args(ac, av) == ERROR)
		return 1;
	params.philos = philos;
	params.forks = forks;
	if (init_params(&params, av) == ERROR)
		return 2;
	if (init_forks(&params) == ERROR)
		return 3;
	init_philos(&params);
	dinner_init(&params);
	printf("time start %ld\n", params.start_time);

	return (0);
}
