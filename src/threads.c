# include "philo.h"

void	*monitor(void *p)
{
	t_args	*args;
	int		all_full;
	int		i;

	args = (t_args *)p;
	while (1)
	{
		all_full = 1;
		i = -1;
		while (++i < args->n_philos)
		{
			pthread_mutex_lock(&args->monitor);
			long time_since_last_meal = get_current_time() - args->philos[i].last_meal_time;
            if (time_since_last_meal > args->philos[i].time_die) {
                args->dead_flag = 1;
                pthread_mutex_lock(&args->print_lock);
                print("died", args->philos[i].nbr, &args->philos[i]);
                pthread_mutex_unlock(&args->print_lock);
                pthread_mutex_unlock(&args->monitor);
				break ;
                return ((void *)0);
            }
			if (args->philos[i].n_meals > 0 && args->philos[i].times_eaten < args->philos[i].n_meals) {
                all_full = 0;
            }
			pthread_mutex_unlock(&args->monitor);
		}
		if (args->n_meals > 0 && all_full) {
            pthread_mutex_lock(&args->monitor);
            args->dead_flag = 1;
            pthread_mutex_unlock(&args->monitor);
			break ;
            return ((void *)0);
        }
	}
	return ((void *)0);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->dead_lock);
	if (philo->args->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->args->dead_lock);
		return(0);
	}
	pthread_mutex_unlock(&philo->args->dead_lock);
	return (1);
}

void    *routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while(check_dead(philo))
	{
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return((void *)0);
}

int	create_thread(t_args *args)
{
	pthread_t	p;
	int			i;

	if (pthread_create(&p, NULL, monitor, &args))
		return (error("Error creating thread", 0));
	i = -1;
	while(++i < args->n_philos)
	{
		if (pthread_create(&args->philos[i].thread, NULL, routine, &args->philos[i]))
			return (error("Error creating thread", 0));
	}
	if (pthread_join(p, NULL))
		return (error("Error joining thread", 0));
	i = -1;
	while(++i < args->n_philos)
	{
		if (pthread_join(args->philos[i].thread, NULL))
			return (error("Error joining thread", 0));
	}
	return (1);
}