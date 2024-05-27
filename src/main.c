# include "philo.h"

void	clear_data(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philos)
		pthread_mutex_destroy(&args->forks[i]);
	pthread_mutex_destroy(&args->print_lock);
	free(args->philos);
	free(args->forks);
}

int	main(int argc, char *argv[])
{
	t_args	args;
	
	if (argc != 5 && argc != 6)
		return (error("Invalid number of args (must be 4 or 5)\n", EXIT_FAILURE));
	if (!check_input(argv))
		return (EXIT_FAILURE);
	if (!init_program(&args, argv))
		return (EXIT_FAILURE);
	if (!create_thread(&args))
		return(EXIT_FAILURE);
	return (0);
}