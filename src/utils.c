# include "philo.h"

u_int64_t   get_time(void)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    // convert tv_sec & tv_usec to millisecond
    return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int is_int(char *str)
{
    while (ft_isdigit(*str))
        str++;
    return (!*str && 1);
}

int check_input(char *argv[])
{
    int i;

    i = 0;
    while(argv[++i])
    {
        if (!is_int(argv[i]))
            return (0);
    }
    return (1);
}