#include "include/philo.h"


void    init_philos_and_forks(struct Philosopher *philos, struct Fork *forks, struct Diner *diner)
{
    int     i;

    i = 0;
    while(i < diner->nb_of_philos)
    {
        philos[i].index = i;
        philos[i].id = i + 1;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % diner->nb_of_philos];
        philos[i].meal_counter = 0;
        philos[i].last_eaten = 0;
        philos[i].diner_infos = diner;
        i++;
    }
    i = 0;
    while(i < diner->nb_of_philos)
    {
        forks[i].index = i;
        pthread_mutex_init(&forks[i].mutex, NULL);
        forks[i].philo_id = -1;
        i++;
    }
}

void init_diner_input(int ac, char **av, struct Diner *diner)
{
    pthread_mutex_init(&diner->is_dead_mutex, NULL);
    pthread_mutex_init(&diner->log_mutex, NULL);
    diner->program_start = time_now_ms(0);
    diner->sb_is_dead = 0;
    diner->dead_philo_id = -1;
    diner->all_ate = 0;
    diner->nb_of_philos = ft_strtoll(av[1]);
    diner->time_to_die = ft_strtoll(av[2]); 
    diner->time_to_eat = ft_strtoll(av[3]);
    diner->time_to_sleep = ft_strtoll(av[4]);
    if (ac == 6 && av[5])
        diner->nb_of_meals = ft_strtoll(av[5]);
    else
        diner->nb_of_meals = NO_MEAL_LIMIT;
}