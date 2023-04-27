/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:17:19 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/27 00:17:33 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	end_threads_mutexes(t_diner *diner)
{
	int		index;

	index = -1;
	while (++index < diner->input.num_philosophers)
		if (pthread_join(diner->philosophers[index].thread, NULL) != 0)
			return (false);
	if (pthread_mutex_destroy(&diner->print_lock) != 0)
		return (false);
	if (pthread_mutex_destroy(&diner->deads_lock) != 0)
		return (false);
	index = -1;
	while (++index < diner->input.num_philosophers)
		if (pthread_mutex_destroy(&diner->forks[index]) != 0)
			return (false);
	return (true);
}

void	free_calloc(t_diner *diner)
{
	if (diner->philosophers)
		free(diner->philosophers);
	if (diner->forks)
		free(diner->forks);
}
