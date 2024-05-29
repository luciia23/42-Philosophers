# include "philo.h"

int	check_dead_flag(t_philo *philo)
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
	if (philo->nbr % 2 == 0)
		ft_usleep(1);
	while(check_dead_flag(philo))
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

	if (pthread_create(&p, NULL, monitor, args))
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