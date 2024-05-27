# include "philo.h"

void    print(char *msg, int nbr, t_philo *philo)
{
    pthread_mutex_lock(&philo->args->print_lock);
    pthread_mutex_unlock(&philo->args->print_lock);
}

void    think(t_philo *philo)
{
    print("is thinking", philo->nbr, philo);
}

void    philo_sleep(t_philo *philo)
{
    print("is sleeping", philo->nbr, philo);
}

void    eat(t_philo *philo)
{

}