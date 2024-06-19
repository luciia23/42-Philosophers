/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:14:52 by lcollado          #+#    #+#             */
/*   Updated: 2024/06/19 21:02:13 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo)
{
	if (philo->args->n_philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print(FORK_MSG, philo->nbr, philo);
		ft_usleep(philo->time_die);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->dead_lock);
	if (philo->args->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->args->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->dead_lock);
	return (1);
}

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->args->start);
	pthread_mutex_unlock(&philo->args->start);
	if (one_philo(philo))
		return ((void *)0);
	if (philo->nbr % 2 == 0)
		ft_usleep(10);
	while (check_dead_flag(philo))
	{
		eat(philo);
		if (philo->times_eaten == philo->n_meals)
			break ;
		philo_sleep(philo);
		think(philo);
	}
	return ((void *)0);
}

void	init_time(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
	{
		args->philos[i].start_time = get_time();
		args->philos[i].last_meal_time = get_time();
	}
}

int	create_philos(t_args *args)
{
	pthread_t	p;
	int			i;

	pthread_mutex_lock(&args->start);
	if (pthread_create(&p, NULL, monitor, args))
		return (error("Error creating thread", 0));
	i = -1;
	while (++i < args->n_philos)
	{
		if (pthread_create(&args->philos[i].thread,
				NULL, routine, &args->philos[i]))
			return (error("Error creating thread", 0));
	}
	init_time(args);
	pthread_mutex_unlock(&args->start);
	if (pthread_join(p, NULL))
		return (error("Error joining thread", 0));
	i = -1;
	while (++i < args->n_philos)
	{
		if (pthread_join(args->philos[i].thread, NULL))
			return (error("Error joining thread", 0));
	}
	return (1);
}
