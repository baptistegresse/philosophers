/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:19:01 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/27 00:33:29 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// a revoir
void	ft_lock_unlock(pthread_mutex_t *mutex, \
int option, t_philosophers *philo)
{
	int		dead_philos;

	if (option == 2)
		pthread_mutex_unlock(mutex);
	check_the_death(philo);
	if (option != 1 || philo->diner->dead_philos == 0)
	{
		pthread_mutex_lock(&philo->diner->deads_lock);
		dead_philos = philo->diner->dead_philos;
		pthread_mutex_unlock(&philo->diner->deads_lock);
		if (dead_philos != 0)
			return ;
	}
	if (option == 1)
		pthread_mutex_lock(mutex);
}

// a revoir
void	eat(t_philosophers *philo)
{
	if (philo->has_eaten == 0 && philo->id % 2 == 0)
	{
		print_status(philo, "is thinking");
		my_usleep(philo, philo->diner->input.ms_eat);
	}
	ft_lock_unlock(&philo->diner->forks[philo->fork1], 1, philo);
	print_status(philo, "has taken a fork");
	ft_lock_unlock(&philo->diner->forks[philo->fork2], 1, philo);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_supper_time = ft_time() - philo->diner->start;
	philo->has_eaten += 1;
	my_usleep(philo, philo->diner->input.ms_eat);
	ft_lock_unlock(&philo->diner->forks[philo->fork1], 2, philo);
	ft_lock_unlock(&philo->diner->forks[philo->fork2], 2, philo);
	print_status(philo, "is sleeping");
	my_usleep(philo, philo->diner->input.ms_sleep);
}

// a revoir
void	*routine(t_philosophers *philosopher)
{
	int		dead_philos;

	usleep(philosopher->diner->start_us - ft_time_microsec());
	while (true)
	{
		eat(philosopher);
		print_status(philosopher, "is thinking");
		my_usleep(philosopher, philosopher->diner->input.ms_think);
		check_the_death(philosopher);
		pthread_mutex_lock(&philosopher->diner->deads_lock);
		dead_philos = philosopher->diner->dead_philos;
		pthread_mutex_unlock(&philosopher->diner->deads_lock);
		if (dead_philos != 0)
			return (NULL);
		if (philosopher->has_eaten == philosopher->meals_needed)
			break ;
	}
	return (NULL);
}

void	print_status(t_philosophers *philo, char *str)
{
	check_the_death(philo);
	if (!is_philosopher_dead(philo))
	{
		pthread_mutex_lock(&philo->diner->print_lock);
		printf("%ld %d %s\n", ft_time() \
		- philo->diner->start, philo->id + 1, str);
		pthread_mutex_unlock(&philo->diner->print_lock);
	}
	check_the_death(philo);
}

// a revoir
int	my_usleep(t_philosophers *philo, time_t sleep_time)
{
	time_t	end_sleep;
	time_t	current_time;
	int		dead_philos;

	end_sleep = ft_time() + sleep_time;
	while (true)
	{
		current_time = ft_time();
		if (current_time >= end_sleep)
		{
			break ;
		}
		check_the_death(philo);
		pthread_mutex_lock(&philo->diner->deads_lock);
		dead_philos = philo->diner->dead_philos;
		pthread_mutex_unlock(&philo->diner->deads_lock);
		if (dead_philos != 0)
		{
			return (0);
		}
		usleep(10);
	}
	return (0);
}
