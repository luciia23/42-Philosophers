/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:25:52 by lcollado          #+#    #+#             */
/*   Updated: 2024/06/19 17:56:06 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# include "../libft/libft.h"
# include "messages.h"

# define PHILO_MAX 200

typedef struct s_philo
{
	int				nbr;
	int				times_eaten;
	long int		last_meal_time;
	long int		start_time;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_meals;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	pthread_mutex_t	internal_mutex;

	struct s_args	*args;
}					t_philo;

typedef struct s_args
{
	int				n_philos;
	int				dead_flag;
	int				n_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	monitor;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	start;

	t_philo			*philos;
}					t_args;

int		check_input(char *argv[]);
int		init_program(t_args *args, char *argv[]);

void	clear_data(t_args *args);

// UTILS
long	get_time(void);
int		error(char *msg, int n_return);
void	ft_usleep(long long time);

// THREADS
int		create_philos(t_args *args);
void	print(char *msg, int nbr, t_philo *philo);
int		check_dead_flag(t_philo *philo);

// ACTIONS
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

// MONITOR
void	*monitor(void *p);
#endif
