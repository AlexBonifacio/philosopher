# Philosophers

A C implementation of the dining philosophers problem for 42 school: one POSIX thread per philosopher, one mutex per fork, and a monitor thread that detects starvation to the millisecond, with no data races.

## The problem

N philosophers sit around a table with N forks. Each one loops through eating, sleeping and thinking, and needs the two forks next to them to eat. A philosopher who does not start eating within `time_to_die` ms of their last meal dies, and the program must report it within 10 ms and stop. The exercise constraints: each philosopher is a thread, each fork is a mutex, shared state must be protected (no data races under ThreadSanitizer/Helgrind), no deadlock, no global variables, and only the allowed libc/pthread functions (`usleep`, `gettimeofday`, `pthread_*`, `printf`, ...). Optionally, the simulation stops once every philosopher has eaten a given number of times.

## Build & run

```sh
cd philo
make          # builds ./philo with -Wall -Wextra -Werror
make clean    # removes obj/
make fclean   # removes obj/ and the binary
make re       # fclean + all
```

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | number of philosophers and forks (1 to 200) |
| `time_to_die` | ms without eating before a philosopher dies |
| `time_to_eat` | ms spent eating (both forks held) |
| `time_to_sleep` | ms spent sleeping |
| `number_of_times_each_philosopher_must_eat` | optional; the simulation ends once every philosopher reached this count |

Arguments must be positive integers (a leading `+` and surrounding whitespace are accepted, `0`, negatives, non-digits and values above `INT_MAX` are rejected with an error message). `main` returns a distinct non-zero exit code for each failing stage (argument parsing, parameter init, fork init, philosopher init, thread start).

Example:

```
$ ./philo 5 800 200 200 3
0 3 is thinking
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
1 2 is thinking
1 4 is thinking
2 1 is thinking
2 1 has taken a fork
2 1 has taken a fork
2 1 is eating
201 3 is sleeping
...
```

Each line is `<timestamp_ms> <philosopher_id> <action>`, timestamps relative to the start of the simulation. States are colour-coded with ANSI escapes. A death prints `<timestamp_ms> <id> died` and is the last line.

## Design

- **One thread per philosopher, one mutex per fork.** Philosophers and forks live in two static arrays of `MAX_PHILOS` (200) entries; there is no heap allocation.
- **Deadlock avoidance by fork ordering.** Odd-numbered philosophers pick up their own fork first, then the left one; even-numbered philosophers do the reverse. Even-numbered philosophers also wait `time_to_eat` before their first attempt, so neighbours are desynchronised from the start.
- **Monitor thread.** A dedicated `end_checker` thread wakes every 200 us, compares each philosopher's `last_eat_time` (read under the shared `table_mutex`) with `time_to_die`, and, when the optional meal count is given, checks whether every philosopher has reached it. Either condition sets the shared `end` flag; all threads poll that flag and exit their loops.
- **Timing.** `gettimeofday` wrapped in `ft_gettimeofday(MSEC|USEC)`; timestamps are computed against a shared `start_time`. `ft_usleep` sleeps in bulk with `usleep` for all but the last ~10 ms, then spins in 100 us steps until the target, and bails out early if the simulation has ended, so long sleeps never delay death detection.
- **Start synchronisation.** Threads are created first and block in `wait_for_start` on a `rdy_to_start` flag. `main` then records `start_time` and flips the flag, so every philosopher starts with the same clock.
- **Single philosopher.** Handled in `one_philo.c`: with one fork there is nothing to eat with, so the thread takes its fork, waits `time_to_die` and dies.
- **No data races.** Every shared read/write goes through `get_/set_bool_mutex` and `get_/set_long_mutex` helpers. Output is serialised with a dedicated `print_mutex`, and `print_action` refuses to print anything after the `end` flag is set, so nothing is logged after a death.
- **Wrapped pthread calls.** `mutex_*_safe` and `thread_*_safe` check every pthread return value and report failures. Init functions roll back already-created mutexes/threads on error.

## Project layout

```
philo/
  Makefile                 # all / clean / fclean / re, auto-dependencies (-MMD -MP)
  include/philo.h          # structs (t_params, t_philo, t_fork), enums, prototypes
  src/
    main.c                 # entry point, thread creation/join, cleanup
    check_args.c           # argument count and format validation
    init_philos.c          # parameter parsing, fork and philosopher setup, fork ordering
    routine.c              # philosopher loop: eat / sleep / think, logging
    monitor.c              # death and meal-count monitor thread
    one_philo.c            # special case for a single philosopher
    utils/
      ft_times.c           # relative timestamps, interruptible ft_usleep
      ft_gettimeofday.c    # gettimeofday in ms or us
      wait_for_start.c     # start barrier
      lock_unlock.c        # mutex-protected getters/setters for bool and long
      mutex_safe.c         # pthread_mutex_* wrappers with error checking
      thread_safe.c        # pthread_create/join/detach wrappers
      bool_forks.c         # lock/unlock a fork
      ft_atol.c, ft_strlen.c, ft_isspace.c, ft_error.c   # minimal libc replacements
```

## Testing

Checked by hand with the standard argument sets (`5 800 200 200`, `4 410 200 200`, `1 800 200 200`, `4 310 200 100` for a required death, `5 800 200 200 7` for the meal limit) and under ThreadSanitizer by enabling the commented `-g3 -fsanitize=thread` flags in the Makefile's `CFLAGS`.
