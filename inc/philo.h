#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# include "../libft/libft.h"

typedef struct s_philo {
    int nbr;
    pthread_t thread;
    //l_fork
    //r_fork

}       t_philo;

typedef struct s_args {
    int n_philos;
    int time_die;
    int time_eat;
    int time_sleep;
    int n_meals;

}           t_args;

int check_input(char *argv[]);
int init_args(t_args args, char *argv[]);


#endif