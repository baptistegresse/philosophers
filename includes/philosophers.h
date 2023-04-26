#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>

# define ERROR_ARGS_NUM "Usage: [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]\n"
# define ERROR_ARGS_DIG "Error: The provided arguments must be positive digits only.\n"
# define ERROR_ARGS_ZER "Error: The provided value cannot be zero. Please enter a positive number greater than zero.\n"

typedef struct s_input t_input;
typedef struct s_diner t_diner;
typedef struct s_philosophers t_philosophers;

typedef struct s_input
{
    int                 num_philosophers;
    time_t              ms_die;
    time_t              ms_eat;
    time_t              ms_sleep;
	time_t              ms_think;
    int                 meals_needed;
}   t_input;

typedef struct s_diner
{
	time_t              start;
    t_input             input;
	t_philosophers	    *philosophers;
	pthread_mutex_t	    *forks;
	pthread_mutex_t	    print_lock;
	pthread_mutex_t	    deads_lock;
	int				    dead_philos;
	time_t              start_us;
}	t_diner;

typedef struct s_philosophers
{
	t_diner			    *diner;
	int					id;
	pthread_t			thread;
	int					meals_needed;
	int					has_eaten;
	int					last_supper_time;
	int					fork1;
	int					fork2;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
}	t_philosophers;

#endif