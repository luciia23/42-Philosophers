# include "philo.h"

void print(char *msg, int nbr, t_philo *philo)
{
    long time;

    pthread_mutex_lock(&philo->args->print_lock);
    time = get_current_time() - philo->start_time;
    if (check_dead_flag(philo))
        printf("%ld %d %s\n", time, nbr, msg);
    pthread_mutex_unlock(&philo->args->print_lock);
}

//only first time? then, it isnt necessary???
void eat(t_philo *philo)
{
    // Si hay solo un filósofo, manejar este caso especial
    if (philo->args->n_philos == 1)
    {
        pthread_mutex_lock(philo->r_fork);
        print(FORK_MSG, philo->nbr, philo);
        ft_usleep(philo->time_die);
        pthread_mutex_unlock(philo->r_fork);
        return;
    }
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

    print(EAT_MSG, philo->nbr, philo);
    pthread_mutex_lock(&philo->args->monitor);
    philo->last_meal_time = get_current_time();
    philo->times_eaten++;
    pthread_mutex_unlock(&philo->args->monitor);

    // Dormir sin mantener los mutexes de los tenedores
    ft_usleep(philo->time_eat);

    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}



// void eat(t_philo *philo)
// {
//     // Primero adquirir siempre el tenedor de menor dirección
//     if (philo->r_fork < philo->l_fork)
//     {
//         pthread_mutex_lock(philo->r_fork);
//         print(FORK_MSG, philo->nbr, philo);
//         pthread_mutex_lock(philo->l_fork);
//         print(FORK_MSG, philo->nbr, philo);
//     }
//     else
//     {
//         pthread_mutex_lock(philo->l_fork);
//         print(FORK_MSG, philo->nbr, philo);
//         pthread_mutex_lock(philo->r_fork);
//         print(FORK_MSG, philo->nbr, philo);
//     }

//     print(EAT_MSG, philo->nbr, philo);
//     pthread_mutex_lock(&philo->args->monitor);
//     philo->last_meal_time = get_current_time();
//     philo->times_eaten++;
//     pthread_mutex_unlock(&philo->args->monitor);

//     // Dormir sin mantener los mutexes de los tenedores
//     ft_usleep(philo->time_eat);

//     pthread_mutex_unlock(philo->r_fork);
//     pthread_mutex_unlock(philo->l_fork);
// }

// void    eat(t_philo *philo)
// {
//     pthread_mutex_lock(philo->r_fork);
//     print(FORK_MSG, philo->nbr, philo);
//     if (philo->args->n_philos == 1)
//     {
//         ft_usleep(philo->time_die);
//         pthread_mutex_unlock(philo->r_fork);
//         return ;
//     }
//     pthread_mutex_lock(philo->l_fork);
//     print(FORK_MSG, philo->nbr, philo);
//     print(EAT_MSG, philo->nbr, philo);
//     pthread_mutex_lock(&philo->args->monitor);
//     philo->last_meal_time = get_current_time();
//     philo->times_eaten++;
//     pthread_mutex_unlock(&philo->args->monitor);
//     //usleep(philo->time_eat * 1000);
//     ft_usleep(philo->time_eat);
//     pthread_mutex_unlock(philo->r_fork);
//     pthread_mutex_unlock(philo->l_fork);
// }

void    think(t_philo *philo)
{
    print(THINK_MSG, philo->nbr, philo);
}

void    philo_sleep(t_philo *philo)
{
    print(SLEEP_MSG, philo->nbr, philo);
    //usleep(philo->time_sleep * 1000);
    ft_usleep(philo->time_sleep);
}
