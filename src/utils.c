# include "philo.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

long   get_current_time(void)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    // convert tv_sec & tv_usec to millisecond
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int error(char *msg, int n_return)
{
    write(2, msg, ft_strlen(msg));
    // if (args)
    //     clear_data(args);
    return (n_return);
}

int is_int(char *str) {
    while (*str) 
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

int check_input(char *argv[])
{
    if (ft_atoi(argv[1]) > PHILO_MAX || !is_int(argv[1]) || ft_atoi(argv[1]) <= 0)
        return (error("Invalid number of philosophers\n", 0));
    if (!is_int(argv[2]) || ft_atoi(argv[2]) <= 0)
        return (error("Invalid time to die\n", 0));
    if (!is_int(argv[3]) || ft_atoi(argv[3]) <= 0)
        return (error("Invalid time to eat\n", 0));
    if (!is_int(argv[4]) || ft_atoi(argv[4]) <= 0)
        return (error("Invalid time to sleep\n", 0));
    if (argv[5] && (!is_int(argv[5]) || ft_atoi(argv[5]) < 0))
        return (error("Invalid number of times each philosophers must eat\n", 0));
    return (1);
}