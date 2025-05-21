

#ifndef PHILO_H
# define PHILO_H

/*Printf malloc free write usleep
 * pthread_create join detach
 * pthread_mutex_init destroy lock unlock
 * gettimeofday
*/
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>
# include <bools.h>

typedef pthread_mutex_t t_mutex;
typedef struct timeval t_timeval;

typedef struct s_fork
{
	t_mutex fork;
	int 	id;
} t_fork;

typedef struct s_philo
{
	int id;
	int eat_count;
	t_fork *l_fork;
	t_fork *r_fork;
	unsigned int last_eat_time;
	pthread_t thread_id;
} t_philo;

typedef struct s_params
{
	unsigned int nb_philos;
	unsigned int time_to_d;
	unsigned int time_to_e;
	unsigned int time_to_s;
	int limit_meals;
	t_timeval start_time;
	bool end;
	t_philo *philos;
	t_fork *forks;
} t_params;

#endif