/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:14:24 by lcollado          #+#    #+#             */
/*   Updated: 2024/06/18 19:17:04 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->nbr % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print(FORK_MSG, philo->nbr, philo);
		pthread_mutex_lock(philo->l_fork);
		print(FORK_MSG, philo->nbr, philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print(FORK_MSG, philo->nbr, philo);
		pthread_mutex_lock(philo->r_fork);
		print(FORK_MSG, philo->nbr, philo);
	}
}

void	one_philo(t_philo *philo)
{
	if (philo->args->n_philos == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print(FORK_MSG, philo->nbr, philo);
		ft_usleep(philo->time_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
}

void	eat(t_philo *philo)
{
	one_philo(philo);
	take_forks(philo);
	print(EAT_MSG, philo->nbr, philo);
	pthread_mutex_lock(&philo->args->monitor);
	philo->last_meal_time = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->args->monitor);
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	think(t_philo *philo)
{
	print(THINK_MSG, philo->nbr, philo);
}

void	philo_sleep(t_philo *philo)
{
	print(SLEEP_MSG, philo->nbr, philo);
	ft_usleep(philo->time_sleep);
}
