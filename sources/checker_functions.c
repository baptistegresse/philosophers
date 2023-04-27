/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:17:07 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/27 10:04:50 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	check_args(int argc, char *argv[])
{
	int		l_index;
	int		w_index;

	if (argc < 5 || argc > 6)
		return (printf(ERROR_ARGS_NUM), false);
	w_index = 0;
	while (++w_index < argc)
	{
		l_index = -1;
		while (argv[w_index][++l_index])
			if (!is_digit(argv[w_index][l_index]))
				return (printf(ERROR_ARGS_DIG), false);
		if (!atoi(argv[w_index]))
			return (printf(ERROR_ARGS_ZER), false);
	}
	return (true);
}

// a revoir
void	check_the_death(t_philosophers *philo)
{
	time_t	current_time;
	time_t	elapsed_time;

	current_time = ft_time();
	elapsed_time = current_time - philo->diner->start;
	if (elapsed_time > (philo->diner->input.ms_die + philo->last_supper_time))
	{
		pthread_mutex_lock(&philo->diner->deads_lock);
		philo->diner->dead_philos++;
		if (philo->diner->dead_philos == 1)
		{
			usleep(10);
			printf("%ld %d %s\n", elapsed_time, philo->id + 1, "has died");
		}
		pthread_mutex_unlock(&philo->diner->deads_lock);
	}
}

bool	is_philosopher_dead(t_philosophers *philo)
{
	int		dead_philos;

	pthread_mutex_lock(&philo->diner->deads_lock);
	dead_philos = philo->diner->dead_philos;
	pthread_mutex_unlock(&philo->diner->deads_lock);
	return (dead_philos != 0);
}

bool	special_case(char *argv[])
{
	if (ft_atoi(argv[1]) == 1)
		return (printf("0 1 has taken a fork\n"),
			printf("%ld 1 died\n", ft_atoi(argv[2])), true);
	return (false);
}
