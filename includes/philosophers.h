/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:05:30 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/27 10:06:39 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>

# define ERROR_ARGS_NUM "Error: Error: Invalid number of arguments.\n"
# define ERROR_ARGS_DIG "Error: The provided arguments must digits only.\n"
# define ERROR_ARGS_ZER "Error: The provided value cannot be zero.\n"

typedef struct s_input			t_input;
typedef struct s_diner			t_diner;
typedef struct s_philosophers	t_philosophers;

typedef struct s_input
{
	int					num_philosophers;
	time_t				ms_die;
	time_t				ms_eat;
	time_t				ms_sleep;
	time_t				ms_think;
	int					meals_needed;
}	t_input;

typedef struct s_diner
{
	time_t				start;
	t_input				input;
	t_philosophers		*philosophers;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		deads_lock;
	int					dead_philos;
	time_t				start_us;
}	t_diner;

typedef struct s_philosophers
{
	t_diner				*diner;
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

// checker_functions.c

bool		check_args(int argc, char *argv[]);
void		check_the_death(t_philosophers *philo);
bool		is_philosopher_dead(t_philosophers *philo);
bool		special_case(char *argv[]);

// destroy_functions.c

bool		end_threads_mutexes(t_diner *diner);
void		free_calloc(t_diner *diner);

// init_functions.c

bool		init_diner(t_diner *diner, char *argv[]);
bool		init_philosophers(t_diner *diner);
bool		init_fork(t_diner *diner);
bool		start_threads(t_diner *diner);

// thread_functions.c

void		*routine(t_philosophers *philosopher);
void		eat(t_philosophers *philo);
void		ft_lock_unlock(pthread_mutex_t *mutex,
				int option, t_philosophers *philo);
void		print_status(t_philosophers *philo, char *str);
int			my_usleep(t_philosophers *philo, time_t sleep_time);

// time_functions.c

time_t		ft_time_microsec(void);
time_t		ft_time(void);

// utils_functions.c

time_t		ft_atoi(const char *str);
bool		is_digit(int c);
void		*ft_calloc(size_t count, size_t size);

#endif