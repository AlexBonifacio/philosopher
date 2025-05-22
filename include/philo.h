

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
# include <stdbool.h>

#define FORK 1
#define EAT 2
#define SLEEP 3

# define RESET       "\033[0m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define BLUE        "\033[34m"
# define BOLD        "\033[1m"

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
	long		 last_eat_time;
	pthread_t thread_id;
} t_philo;

typedef struct s_params
{
	unsigned int	nb_philos;
	long			time_to_d;
	long			time_to_e;
	long			time_to_s;
	int 			limit_meals;
	t_timeval		*start_time;
	bool			end;
	t_philo			*philos;
	t_fork			*forks;
} t_params;


/************************************************/

long 	ft_atol(const char *str);
void 	ft_exit(char *str);
size_t 	ft_strlen(const char *str);
int 	ft_isspace(int c);
void 	check_args(int ac, char **av);


#endif