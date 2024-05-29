# include "philo.h"

// void    print(char *msg, int nbr, t_philo *philo)
// {
//     long    time;

//     pthread_mutex_lock(&philo->args->print_lock);
//     time = get_current_time() - philo->start_time;
//     if (check_dead(philo))
//         printf("%zu %d %s\n",time, nbr, msg);
//     pthread_mutex_unlock(&philo->args->print_lock);
// }

// int	ft_usleep(int time)
// {
// 	int	start;

// 	start = get_current_time();
// 	while ((get_current_time() - start) < time)
// 		usleep(time / 10);
// 	return (0);
// }


void print(char *msg, int nbr, t_philo *philo)
{
    long time;

    pthread_mutex_lock(&philo->args->print_lock);
    time = get_current_time() - philo->start_time;
    printf("%ld %d %s\n", time, nbr, msg);
    pthread_mutex_unlock(&philo->args->print_lock);
}


void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print(FORK_MSG, philo->nbr, philo);
    pthread_mutex_lock(philo->l_fork);
    print(FORK_MSG, philo->nbr, philo);
    print(EAT_MSG, philo->nbr, philo);
    //pthread_mutex_lock(&philo->args->monitor);
    philo->last_meal_time = get_current_time();
    philo->times_eaten++;
   // pthread_mutex_unlock(&philo->args->monitor);
    //usleep(philo->time_eat * 1000);
    ft_usleep(philo->time_eat);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);

}

void eat_func(t_philo *philo) 
{
    t_args *args = philo->args;
    pthread_mutex_lock(philo->l_fork);
    pthread_mutex_lock(philo->r_fork);
    pthread_mutex_lock(&args->monitor);
    philo->last_meal_time = get_current_time();
    philo->times_eaten++;
    pthread_mutex_unlock(&args->monitor);
    pthread_mutex_lock(&args->print_lock);
    printf("Philosopher %d is eating\n", philo->nbr);
    pthread_mutex_unlock(&args->print_lock);
    usleep(philo->time_eat * 1000);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

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
