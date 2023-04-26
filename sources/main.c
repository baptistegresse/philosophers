#include "../includes/philosophers.h"

time_t	ft_time_microsec(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + (tv.tv_usec));
}

time_t	ft_atoi(const char *str)
{
	time_t	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (i == 0 || str[i] != '\0' || result > 2147483647)
		return (0);
	return (result);
}

bool is_digit(int c)
{
    return c >= '0' && c <= '9';
}

void	ft_bzero(void *s, size_t n)
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

bool    check_args(int argc, char *argv[])
{
    int     l_index;
    int     w_index;

    if (argc < 5 || argc > 6)
        return (printf(ERROR_ARGS_NUM), false);
    w_index = 0;
    while (++w_index < argc)
    {
        l_index = -1;
        while (argv[w_index][++l_index])
            if (!is_digit(argv[w_index][l_index]))
                return (printf(ERROR_ARGS_DIG), false);
    }
    w_index = 0;
    while (++w_index < argc)
        if (!atoi(argv[w_index]))
            return (printf(ERROR_ARGS_ZER), false);
    return (true);
}

bool    init_diner(t_diner *diner, int argc, char *argv[])
{
    diner->input.num_philosophers = atoi(argv[1]);
    diner->input.ms_die = atoi(argv[2]);
    diner->input.ms_eat = atoi(argv[3]);
    diner->input.ms_sleep = atoi(argv[4]);
    diner->input.meals_needed = -1;
    if (argv[5])
        diner->input.meals_needed = atoi(argv[5]);
    if (diner->input.num_philosophers % 2 == 0)
        diner->input.ms_think = (diner->input.ms_eat - diner->input.ms_sleep) / 2;
    diner->start = (ft_time_microsec() + 1000000) / 1000;
    diner->start_us = ft_time_microsec() + 1000000;
    diner->dead_philos = 0;
    if (pthread_mutex_init(&diner->print_lock, NULL) != 0)
        return (false);
    if (pthread_mutex_init(&diner->deads_lock, NULL) != 0)
        return (false);
    diner->philosophers = calloc(sizeof(t_philosophers), diner->input.num_philosophers);
    if (!diner->philosophers)
        return (false);
    return (true);
}

bool    special_case(char *argv[])
{
    if (ft_atoi(argv[1]) == 1)
        return (printf("0 1 has taken a fork\n"),
        printf("%ld 1 died\n", ft_atoi(argv[2])), true);
    return (false);
}

bool    init_fork(t_diner *diner)
{
    int     index;

    diner->forks = ft_calloc(sizeof(pthread_mutex_t), diner->input.num_philosophers);
    if (!diner->forks)
        return (false);
    index = -1;
    while (++index < diner->input.num_philosophers)
        if (pthread_mutex_init(&diner->forks[index], NULL) != 0)
            return (false);
    return (true);
}

bool    init_philosophers(t_diner *diner)
{
    int     index;

    index = -1;
    while (++index < diner->input.num_philosophers)
    {
        diner->philosophers[index].diner = diner;
        diner->philosophers[index].meals_needed = diner->input.meals_needed;
        diner->philosophers[index].id = index;
        diner->philosophers[index].fork1 = diner->philosophers[index].id;
        diner->philosophers[index].fork2 = (diner->philosophers[index].id + 1) % diner->input.num_philosophers;
    }
    printf("loading...\n\n");
    return (true);
}

void    *routine(void *arg)
{
    (void)arg;
    return (NULL);
}

bool    start_threads(t_diner *diner)
{
    int     index;

    index = -1;
    while (++index < diner->input.num_philosophers)
        if (pthread_create(&diner->philosophers[index].thread, NULL, &routine, &diner->philosophers[index]) != 0)
            return (false);
    usleep(100);
    return (true);
}

bool    end_threads_mutexes(t_diner *diner)
{
    int     index;

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

bool    free_calloc(t_diner *diner)
{
    int     index;

    index = -1;
    while (&diner->philosophers[++index])
        free(&diner->philosophers[index]);
    if (diner->philosophers)
        free(diner->philosophers);
    if (diner->forks)
        free(diner->forks);
}

int main(int argc, char *argv[])
{
    t_diner     diner;

    if (!check_args(argc, argv))
        return (1);
    if (special_case(argv))
        return (0);
    if (!init_diner(&diner, argc, argv))
        return (2);
    if (!init_fork(&diner))
        return (3);
    if (!init_philosophers(&diner))
        return (4);
    if (!start_threads(&diner))
        return (5);
    if (!end_threads_mutexes(&diner))
        return (6);
    if (!free_calloc(&diner))
        return (7);
    return (0);
}
