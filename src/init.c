# include "philo.h"

int init_args(t_args *args, char *argv[])
{
    args->n_philos = ft_atoi(argv[1]);
    if (args->n_philos > 200)
        return (0);
    args->time_die = ft_atoi(argv[2]);
    args->time_eat = ft_atoi(argv[3]);
    args->time_sleep = ft_atoi(argv[4]);
    if(argv[5])
        args->n_meals = ft_atoi(argv[5]);
    return (1);
}

void    init_philos()
{

}

