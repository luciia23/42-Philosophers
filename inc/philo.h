#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# include "../libft/libft.h"
# include "messages.h"

# define PHILO_MAX 200

typedef struct s_philo {
    int         nbr;
    int         times_eaten;
    long        last_meal_time;
    int time_die;
    int time_eat;
    int time_sleep;
    int n_meals;
    pthread_t   thread;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    struct s_args *args;
}       t_philo;

typedef struct s_args {
    int n_philos;
    int dead_flag;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t monitor;
    t_philo *philos;
}           t_args;

int     check_input(char *argv[]);
int	init_program(t_args *args, char *argv[]);

void	clear_data(t_args *args);

// UTILS
long   get_current_time(void);
int error(char *msg, int n_return);

// THREADS
int	create_thread(t_args *args);

// ACTIONS
void    eat(t_philo *philo);
void    philo_sleep(t_philo *philo);
void    think(t_philo *philo);


#endif