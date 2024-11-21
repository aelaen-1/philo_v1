#include "include/philo.h"

static void    join_threads(struct Fork *forks, struct Philosopher *philos, struct Diner *diner)
{
    int     i;
    
    i = 0;
    while(i < diner->nb_of_philos)
    {
        if(pthread_join(philos[i].thread, NULL) != 0)
        {
            clean_mutex(forks, diner);
            printf("Couldn't join thread of philo %d\n", philos->id);
            //return ; ? 
        }
        i++;
    }
}


void    thread_create_and_join(struct Fork *forks, struct Philosopher *philos, struct Diner *diner)
{
    int     i;

    i = 0;
    while (i < diner->nb_of_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, start_living, &philos[i]) != 0)
        {
            printf("Couldn't create thread of philo %d\n", philos->id);
            clean_mutex(forks, diner);
            //return ; ? 
        }
        i++;
    }
    join_threads(forks, philos, diner);
}