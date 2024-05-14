# include "philo.h"

int main(int argc, char *argv[])
{
    t_args  args;

    if (((argc == 5 || argc == 6) && 
        check_input(argv)))
    {
        init_args(args, argv);
    }
    else
        printf("Invalid arguments");
    return (0);
}