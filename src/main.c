/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:53:20 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/29 23:52:45 by abonifac         ###   ########.fr       */
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
/*
 * to avoid all philosopher printing at the same time ?
*/
void print_action(t_params *params, t_philo *philo, t_philo_action action)
{
	mutex_lock_safe(&params->print_mutex);
	if (action == P_DEAD)
	{
		printf(RED BOLD"%ld %d is dead\n"RESET, print_time(params),philo->id);
		set_bool_mutex(&params->table_mutex, &params->end, true);
		mutex_unlock_safe(&params->print_mutex);
		return ;
	}
	// print_time(params);
	
	if (get_bool_mutex(&params->table_mutex, &params->end) == true)
	{
		mutex_unlock_safe(&params->print_mutex);
		return;
	}
	if (action == P_EATING)
	{
		printf("%ld %d is"GREEN " eating\n"RESET, print_time(params),philo->id);
		// ft_usleep(params->time_to_e * 1000, params);
	}
	else if (action == P_SLEEPING)
	{
		printf("%ld %d is"BLUE" sleeping\n"RESET, print_time(params),philo->id);
		// ft_usleep(params->time_to_s * 1000, params);
	}
	else if (action == P_THINKING)
	{
		printf("%ld %d is"PURP " thinking\n"RESET, print_time(params),philo->id);
	}

	else if (action == P_FFORK_TAKEN)
	{
		printf("%ld %d has taken a fork\n", print_time(params),philo->id);
	}
	else if (action == P_SFORK_TAKEN)
	{
		printf("%ld %d has taken a fork\n", print_time(params),philo->id);
	}
	mutex_unlock_safe(&params->print_mutex);
}

void eat(t_philo *philo)
{
	t_params *params;

	params = philo->params;
	if (get_bool_mutex(&params->table_mutex, &params->end))
		return ;
	mutex_lock_safe(&philo->f_fork->m_fork);
	if (get_bool_mutex(&params->table_mutex, &params->end))
    {
        mutex_unlock_safe(&philo->f_fork->m_fork);
        return ;
    }
	mutex_lock_safe(&philo->s_fork->m_fork);
	if (get_bool_mutex(&params->table_mutex, &params->end))
    {
		mutex_unlock_safe(&philo->s_fork->m_fork);
        mutex_unlock_safe(&philo->f_fork->m_fork);
        return ;
    }
	print_action(params, philo, P_FFORK_TAKEN);
	print_action(params, philo, P_SFORK_TAKEN);
	set_long_mutex(&params->table_mutex, &philo->last_eat_time, print_time(params));
	if (get_bool_mutex(&params->table_mutex, &params->end) == false)
    {
        print_action(params, philo, P_EATING);
        philo->eat_count++;
        ft_usleep(params->time_to_e * 1000, params);
    }
	if (params->limit_meals != -1 && philo->eat_count >= params->limit_meals)
	{
		set_bool_mutex(&philo->philo_mutex, &philo->is_full, true);
		// printf("coucou\n");
	}
	mutex_unlock_safe(&philo->f_fork->m_fork);
	mutex_unlock_safe(&philo->s_fork->m_fork);
}

void think(t_philo *philo, t_params *params)
{
	long time_to_think = params->time_to_e - params->time_to_s;
	
	if (time_to_think < 0)
		time_to_think = -time_to_think;
	print_action(params, philo, P_THINKING);
	ft_usleep(time_to_think * 1000 + 100, params);
}
void	*dinner_routine(void *arg)
{
	t_philo		*philo = (t_philo *)arg;
	t_params	*p = philo->params;

	wait_for_start(p);
	if (philo->id % 2 == 0)
		ft_usleep(p->time_to_e * 1000, p);

	while (true)
	{
		if (get_bool_mutex(&p->table_mutex, &p->end))
			break;

		eat(philo);
		if (get_bool_mutex(&p->table_mutex, &p->end))
			break;

		print_action(p, philo, P_SLEEPING);
		ft_usleep(p->time_to_s * 1000, p);
		if (get_bool_mutex(&p->table_mutex, &p->end))
			break;

		if (p->nb_philos % 2 == 1)
		{
			think(philo, p);
			if (get_bool_mutex(&p->table_mutex, &p->end))
				break;
		}
	}
	return NULL;
}

void *death_checker(void *arg)
{
	t_params *param;
	int i;
	long now;
	
	param = (t_params *)arg;
	wait_for_start(param);
	while (get_bool_mutex(&param->table_mutex, &param->end) == false)
	{
		now = print_time(param);
		i = 0;
		mutex_lock_safe(&param->table_mutex);
		while (i < param->nb_philos)
		{
			// int y = 0;
			if (now - param->philos[i].last_eat_time > param->time_to_d)
			{
				param->end = true;
				mutex_unlock_safe(&param->table_mutex);
				print_action(param, &param->philos[i], P_DEAD);
				return arg;
			}
			// if (get_bool_mutex(&param->philos[i].philo_mutex, &param->philos[i].is_full) == true)
			// {
			// 	printf("y = %d\n", y);
			// 	y++;
			// }
			// if (y == param->nb_philos)
			// {
			// 	printf("y = %d", y);
			// 	param->end = true;
			// 	mutex_unlock_safe(&param->table_mutex);
			// 	return arg;
			// }
			i++;
		}
		mutex_unlock_safe(&param->table_mutex);
		ft_usleep(500, param);
	}
	return arg;
}

void *one_philo(void *arg)
{
	t_philo *philo;
	t_params *params;

	philo = (t_philo *)arg;
	params = philo->params;
	params->start_time = ft_gettimeofday(MSEC);
	print_action(params, philo, P_FFORK_TAKEN);
	ft_usleep(params->time_to_d * 1000, params);
	print_action(params, philo, P_DEAD);
	set_bool_mutex(&params->table_mutex, &params->end, true);
	return NULL;
}

int dinner_init(t_params *params)
{
	int i;
	int	status;
	
	i = 0;
	status = NO_ERR;
	if (params->nb_philos == 1)
	{
		status = thread_create_safe(&params->philos[0].thread_id, one_philo, &params->philos[0]);
		thread_join_safe(&params->philos[0].thread_id);
		return status;
	}

	while (i < params->nb_philos)
	{
		status = thread_create_safe(&params->philos[i].thread_id, dinner_routine, &params->philos[i]);
		set_long_mutex(&params->table_mutex, &params->philos[i].last_eat_time, params->start_time);
		if (status == ERROR)
			break;
		i++;
	}
	params->start_time = ft_gettimeofday(MSEC);
	set_bool_mutex(&params->table_mutex, &params->rdy_to_start, true);
	status = thread_create_safe(&params->death, death_checker, params);
	if (status == ERROR)
	{
		while (--i >= 0)
			thread_detach_safe(&params->philos[i].thread_id);
		while (++i < params->nb_philos)
			mutex_destroy_safe(&params->forks[i].m_fork);
		return status;
	}
	i = 0;
	while (i < params->nb_philos)
	{
		thread_join_safe(&params->philos[i].thread_id);
		i++;
	}
	thread_join_safe(&params->death);
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

	return (0);
}
