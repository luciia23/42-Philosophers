# include "philo.h"

void    *routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while(!philo->args->dead_flag)
	{
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return((void *)0);
}

int	create_thread(t_args *args)
{
	int	i;

	//TO:DO -> destroying the mutex
	i = -1;
	while(++i < args->n_philos)
	{
		if (pthread_create(&args->philos[i].thread, NULL, routine, &args->philos[i]))
			error("Error creating thread", 0);
	}
	i = -1;
	while(++i < args->n_philos)
	{
		if (pthread_join(args->philos[i].thread, NULL))
			error("Error joining thread", 0);
	}
	return (1);
}