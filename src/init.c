/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:14:13 by lcollado          #+#    #+#             */
/*   Updated: 2024/06/18 19:17:25 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_philo *philos, char *argv[], int n_philos)
{
	int	i;

	i = -1;
	while (++i < n_philos)
	{
		philos[i].time_die = ft_atoi(argv[2]);
		philos[i].time_eat = ft_atoi(argv[3]);
		philos[i].time_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philos[i].n_meals = ft_atoi(argv[5]);
		else
			philos[i].n_meals = -1;
	}
	return (1);
}

void	init_philos(t_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->n_philos)
	{
		philos[i].nbr = i + 1;
		philos[i].times_eaten = 0;
		philos[i].last_meal_time = get_time();
		philos[i].start_time = get_time();
		philos[i].l_fork = &args->forks[i];
		philos[i].r_fork = &args->forks[(i + 1) % args->n_philos];
		args->philos[i].args = args;
		i++;
	}
}

void	init_forks(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
		pthread_mutex_init(&args->forks[i], NULL);
}

int	alloc(t_args *args)
{
	args->philos = (t_philo *)malloc(sizeof(t_philo) * args->n_philos);
	if (!args->philos)
		error(ERR_ALLOC1, 0);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->n_philos);
	if (!args->forks)
		error(ERR_ALLOC2, 0);
	return (1);
}

int	init_program(t_args *args, char *argv[])
{
	args->dead_flag = 0;
	args->n_philos = ft_atoi(argv[1]);
	if (!alloc(args))
		return (0);
	init_args(args->philos, argv, args->n_philos);
	init_forks(args);
	init_philos(args, args->philos);
	pthread_mutex_init(&args->monitor, NULL);
	pthread_mutex_init(&args->print_lock, NULL);
	pthread_mutex_init(&args->dead_lock, NULL);
	pthread_mutex_init(&args->meal_lock, NULL);
	return (1);
}
