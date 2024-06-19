/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:14:42 by lcollado          #+#    #+#             */
/*   Updated: 2024/06/19 19:19:38 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_args *args)
{
	int		i;
	long	last_meal;

	i = -1;
	while (++i < args->n_philos)
	{
		pthread_mutex_lock(&args->monitor);
		last_meal = get_time() - args->philos[i].last_meal_time;
		if (last_meal > args->philos[i].time_die)
		{
			print("died", args->philos[i].nbr, &args->philos[i]);
			pthread_mutex_lock(&args->dead_lock);
			args->dead_flag = 1;
			pthread_mutex_unlock(&args->dead_lock);
			pthread_mutex_unlock(&args->monitor);
			return (1);
		}
		pthread_mutex_unlock(&args->monitor);
	}
	return (0);
}

int	check_meals(t_args *args)
{
	int	i;
	int	all_full;

	all_full = 1;
	i = -1;
	if (args->philos[0].n_meals > 0)
	{
		while (++i < args->n_philos)
		{
			pthread_mutex_lock(&args->monitor);
			if (args->philos[i].n_meals > 0
				&& args->philos[i].times_eaten < args->philos[i].n_meals)
				all_full = 0;
			pthread_mutex_unlock(&args->monitor);
		}
		if (args->philos[0].n_meals > 0 && all_full)
		{
			pthread_mutex_lock(&args->dead_lock);
			args->dead_flag = 1;
			pthread_mutex_unlock(&args->dead_lock);
			return (1);
		}
	}
	return (0);
}

void	*monitor(void *p)
{
	t_args	*args;

	args = (t_args *)p;
	pthread_mutex_lock(&args->start);
	pthread_mutex_unlock(&args->start);
	while (1)
	{
		if (check_dead(args) || check_meals(args))
			break ;
	}
	return ((void *)0);
}
