/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:17:47 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/27 00:30:26 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	init_diner(t_diner *diner, char *argv[])
{
	diner->input.num_philosophers = atoi(argv[1]);
	diner->input.ms_die = atoi(argv[2]);
	diner->input.ms_eat = atoi(argv[3]);
	diner->input.ms_sleep = atoi(argv[4]);
	diner->input.meals_needed = -1;
	if (argv[5])
		diner->input.meals_needed = atoi(argv[5]);
	if (diner->input.num_philosophers % 2 == 0)
		diner->input.ms_think = (diner->input.ms_eat
				- diner->input.ms_sleep) / 2;
	diner->start = (ft_time_microsec() + 1000000) / 1000;
	diner->start_us = ft_time_microsec() + 1000000;
	diner->dead_philos = 0;
	if (pthread_mutex_init(&diner->print_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&diner->deads_lock, NULL) != 0)
		return (false);
	diner->philosophers = ft_calloc(sizeof(t_philosophers),
			diner->input.num_philosophers);
	if (!diner->philosophers)
		return (false);
	return (true);
}

bool	init_philosophers(t_diner *diner)
{
	int		index;

	index = -1;
	while (++index < diner->input.num_philosophers)
	{
		diner->philosophers[index].diner = diner;
		diner->philosophers[index].meals_needed = diner->input.meals_needed;
		diner->philosophers[index].id = index;
		diner->philosophers[index].fork1 = diner->philosophers[index].id;
		diner->philosophers[index].fork2 \
		= (diner->philosophers[index].id + 1) % diner->input.num_philosophers;
	}
	return (true);
}

bool	init_fork(t_diner *diner)
{
	int		index;

	diner->forks = ft_calloc(sizeof(pthread_mutex_t), \
	diner->input.num_philosophers);
	if (!diner->forks)
		return (false);
	index = -1;
	while (++index < diner->input.num_philosophers)
		if (pthread_mutex_init(&diner->forks[index], NULL) != 0)
			return (false);
	return (true);
}

bool	start_threads(t_diner *diner)
{
	int		index;

	index = -1;
	while (++index < diner->input.num_philosophers)
		if (pthread_create(&diner->philosophers[index].thread, NULL, \
			(void *)&routine, &diner->philosophers[index]) != 0)
			return (false);
	usleep(100);
	return (true);
}
