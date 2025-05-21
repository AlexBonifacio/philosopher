

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

#endif