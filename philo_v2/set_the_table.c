#include "include/philo.h"

int     pthread_create_join(struct Philosopher *philos, struct Fork *forks, struct Diner *diner)
{
    int     i;

    i = 0;
    while(i < diner->nb_of_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, start_living, &philos[i]))
        {
            clean_mutex(forks, diner);
            return(printf("Could not create a thread\n"), 0);
        }
        i++;
    }
    i = 0;
    while(i < diner->nb_of_philos)
    {
        if (pthread_join(philos[i].thread, NULL))
        {
            clean_mutex(forks, diner);
            return(printf("Could not join a thread\n"), 0);
        }
        i++;
    }
    return (1);
}

int    init_philos_and_forks(struct Philosopher *philos, struct Fork *forks, struct Diner *diner)
{
    int     i;

    i = 0;
    while(i < diner->nb_of_philos)
    {
        forks[i].index = i;
        if(pthread_mutex_init(&forks[i].mutex, NULL))
            return (printf("Could not create fork mutex\n"), 0);
        forks[i].philo_id = -1;
        i++;
    }
    i = 0;
    while(i < diner->nb_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % diner->nb_of_philos];
        philos[i].meal_counter = 0;
        philos[i].last_eaten = 0;
        philos[i].diner_infos = diner;
        i++;
    }
    return (1);
}

int init_input(int ac, char **av, struct Diner *diner)
{
    if (pthread_mutex_init(&diner->is_dead_mutex, NULL))
        return (printf("Could not init is_dead_mutex\n"), 0);
    if (pthread_mutex_init(&diner->log_mutex, NULL))
        return (printf("Could not init log_mutex.\n"), 0);
    if (pthread_mutex_init(&diner->all_ate_mutex, NULL))
        return (printf("Could not init all_ate_mutex\n"), 0);
    diner->program_start = time_now_ms(0);
    diner->sb_is_dead = 0;
    diner->all_ate = 0;
    diner->dead_philo_id = -1;
    diner->nb_of_philos = ft_strtoll(av[1]);
    diner->time_to_die = ft_strtoll(av[2]); 
    diner->time_to_eat = ft_strtoll(av[3]);
    diner->time_to_sleep = ft_strtoll(av[4]);
    if (ac == 6 && av[5])
        diner->nb_of_meals = ft_strtoll(av[5]);
    else
        diner->nb_of_meals = NO_MEAL_LIMIT;
    return (1);
}

void    clean_mutex(struct Fork *forks, struct Diner *diner)
{
    int     i;

    i = 0;
    while (i < diner->nb_of_philos)
    {
        pthread_mutex_destroy(&forks[i].mutex);
        i++;
    }
    pthread_mutex_destroy(&diner->log_mutex);
    pthread_mutex_destroy(&diner->is_dead_mutex);
    pthread_mutex_destroy(&diner->all_ate_mutex);
}