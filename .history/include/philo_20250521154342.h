

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

typedef pthread_mutex_t t_mutex;

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
	int last_eat_time;
	pthread_t thread_id;
} t_philo;

typedef struct s_params{
	int nb_philos;
	int time_to_d;
	int time_to_e;
	int time_to_s;
	int 
}

#endif