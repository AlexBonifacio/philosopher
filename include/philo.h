

#ifndef PHILO_H
#define PHILO_H

/*Printf malloc free write usleep
 * pthread_create join detach
 * pthread_mutex_init destroy lock unlock
 * gettimeofday
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

#ifndef MAX_PHILOS
#define MAX_PHILOS 200
#endif

#define NO_ERR 1
#define ERROR 0

#define MSEC 1
#define USEC 2

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define PURP "\033[35m"

typedef pthread_mutex_t t_mutex;
typedef struct timeval t_timeval;
typedef struct s_params t_params;

typedef struct s_fork
{
	t_mutex m_fork;
	int id;
} t_fork;

typedef struct s_philo
{
	int id;
	int eat_count;
	bool is_full;
	long last_eat_time;
	t_fork *f_fork;
	t_fork *s_fork;
	pthread_t thread_id;
	t_params *params;
	t_mutex philo_mutex;
} t_philo;

struct s_params
{
	int nb_philos;
	long time_to_d;
	long time_to_e;
	long time_to_s;
	int limit_meals;
	long start_time;
	bool end;
	bool rdy_to_start;
	pthread_t death;
	t_mutex table_mutex;
	t_philo *philos;
	t_fork *forks;
	t_mutex print_mutex;
};

typedef enum e_philo_action
{
	P_EATING,
	P_SLEEPING,
	P_THINKING,
	P_DEAD,
	P_FFORK_TAKEN,
	P_SFORK_TAKEN,

} t_philo_action;

/************************************************/

long ft_atol(const char *str);
int ft_error(char *str);
size_t ft_strlen(const char *str);
int ft_isspace(int c);
int check_args(int ac, char **av);
long ft_gettimeofday(int flag);
void wait_for_start(t_params *params);
long print_time(t_params *params);
void ft_usleep(long time_in_us, t_params *params);

// int 	mutex_safe_call(t_mutex *mutex);
int mutex_init_safe(t_mutex *mutex);
int mutex_destroy_safe(t_mutex *mutex);
int mutex_lock_safe(t_mutex *mutex);
int mutex_unlock_safe(t_mutex *mutex);

int thread_create_safe(pthread_t *thread, void *(*func)(void *), void *arg);
int thread_join_safe(pthread_t *thread);
int thread_detach_safe(pthread_t *thread);
// int thread_safe_call(pthread_t *thread, void *(*func)(void *), void *arg);
long get_long_mutex(t_mutex *mutex, long *value);
void set_long_mutex(t_mutex *mutex, long *dest, long value);
bool get_bool_mutex(t_mutex *mutex, bool *value);
void set_bool_mutex(t_mutex *mutex, bool *dest, bool value);

#endif