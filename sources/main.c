/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:18:49 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/27 10:06:42 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char *argv[])
{
	t_diner		diner;

	if (!check_args(argc, argv))
		return (1);
	if (special_case(argv))
		return (0);
	if (!init_diner(&diner, argv))
		return (2);
	if (!init_fork(&diner))
		return (3);
	if (!init_philosophers(&diner))
		return (4);
	if (!start_threads(&diner))
		return (5);
	if (!end_threads_mutexes(&diner))
		return (6);
	free_calloc(&diner);
	return (0);
}
