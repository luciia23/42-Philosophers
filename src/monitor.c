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
            print("died", args->philos[i].nbr, &args->philos[i]);
            args->dead_flag = 1;
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
            all_full = 0;
        pthread_mutex_unlock(&args->monitor);
    }
    if (args->philos[0].n_meals > 0 && all_full)
    {
        pthread_mutex_lock(&args->dead_lock);
        args->dead_flag = 1;
        pthread_mutex_unlock(&args->dead_lock);
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
            break ;
	}
	return ((void *)0);
}

