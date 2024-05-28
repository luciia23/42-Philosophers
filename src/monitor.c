#include "philo.h"

int check_dead(t_args *args)
{
    int i;

    i = -1;
    while (++i < args->n_philos)
    {
        pthread_mutex_lock(&args->monitor);
        long time_since_last_meal = get_current_time() - args->philos[i].last_meal_time;
        if (time_since_last_meal > args->philos[i].time_die)
        {
            args->dead_flag = 1;
            print("died", args->philos[i].nbr, &args->philos[i]);
            pthread_mutex_unlock(&args->monitor);
            return (1); // Return 1 indicates a philosopher has died
        }
        pthread_mutex_unlock(&args->monitor);
    }
    return (0); // Return 0 indicates no philosopher has died
}

int check_full(t_args *args)
{
    int i;
    int all_full;

    all_full = 1;
    i = -1;
    while (++i < args->n_philos)
    {
        pthread_mutex_lock(&args->monitor);
        if (args->philos[i].n_meals > 0 && args->philos[i].times_eaten < args->philos[i].n_meals)
        {
            all_full = 0;
        }
        pthread_mutex_unlock(&args->monitor);
    }
    if (args->philos[0].n_meals > 0 && all_full)
    {
        pthread_mutex_lock(&args->monitor);
        args->dead_flag = 1;
        pthread_mutex_unlock(&args->monitor);
        return (1); // Return 1 indicates all philosophers are full
    }
    return (0); // Return 0 indicates not all philosophers are full
}

void	*monitor(void *p)
{
	t_args	*args;

	args = (t_args *)p;
	while (1)
	{
        if (check_dead(args) || check_full(args))
            return ((void *)0);
	}
	return ((void *)0);
}

// // Monitor thread routine

// void	*monitor(void *pointer)
// {
// 	t_philo	*philos;

// 	philos = (t_philo *)pointer;
// 	while (1)
// 		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
// 			break ;
// 	return (pointer);
// }


// // Checks if the philosopher is dead

// int	philosopher_dead(t_philo *philo, size_t time_to_die)
// {
// 	pthread_mutex_lock(philo->meal_lock);
// 	if (get_current_time() - philo->last_meal >= time_to_die
// 		&& philo->eating == 0)
// 		return (pthread_mutex_unlock(philo->meal_lock), 1);
// 	pthread_mutex_unlock(philo->meal_lock);
// 	return (0);
// }

// // Check if any philo died

// int	check_if_dead(t_philo *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philos[0].num_of_philos)
// 	{
// 		if (philosopher_dead(&philos[i], philos[i].time_to_die))
// 		{
// 			print_message("died", &philos[i], philos[i].id);
// 			pthread_mutex_lock(philos[0].dead_lock);
// 			*philos->dead = 1;
// 			pthread_mutex_unlock(philos[0].dead_lock);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// // Checks if all the philos ate the num_of_meals

// int	check_if_all_ate(t_philo *philos)
// {
// 	int	i;
// 	int	finished_eating;

// 	i = 0;
// 	finished_eating = 0;
// 	if (philos[0].num_times_to_eat == -1)
// 		return (0);
// 	while (i < philos[0].num_of_philos)
// 	{
// 		pthread_mutex_lock(philos[i].meal_lock);
// 		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
// 			finished_eating++;
// 		pthread_mutex_unlock(philos[i].meal_lock);
// 		i++;
// 	}
// 	if (finished_eating == philos[0].num_of_philos)
// 	{
// 		pthread_mutex_lock(philos[0].dead_lock);
// 		*philos->dead = 1;
// 		pthread_mutex_unlock(philos[0].dead_lock);
// 		return (1);
// 	}
// 	return (0);
// }

