/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgresse <bgresse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:20:14 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/27 00:21:59 by bgresse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

time_t	ft_atoi(const char *str)
{
	time_t	result;
	int		index;

	result = 0;
	index = 0;
	while (is_digit(str[index]))
	{
		result = result * 10 + (str[index] - '0');
		index++;
	}
	if (index == 0 || str[index] != '\0' || result > 2147483647)
		return (0);
	return (result);
}

bool	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tab;

	tab = s;
	while (n--)
		*(tab++) = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
