#include "include/philo.h"

// int     everyone_ate(struct Diner *diner)
// {
//     if (diner->nb_of_meals == NO_MEAL_LIMIT)
//         return (0);
//     if (diner->all_ate == (diner->nb_of_philos * diner->nb_of_meals))
//         return (1);
//     return (0);
// }

// int check_if_dead(struct Philosopher *p)
// {
//     if (p->diner_infos->sb_is_dead)
//         return (1);
//     if (time_now_ms(p->diner_infos->program_start) - p->last_eaten >= p->diner_infos->time_to_die)
//     {
//         if (!pthread_mutex_lock(&p->diner_infos->is_dead_mutex) && !(p->diner_infos->sb_is_dead))
//         {
//             p->diner_infos->dead_philo_id = p->id;
//             p->diner_infos->sb_is_dead = 1;
//         }
//         pthread_mutex_unlock(&p->diner_infos->is_dead_mutex);
//         return (1);
//     }
//     return (0);
// }


            // END BECAUSE EVERYONE ATE ENOUGH
int everyone_ate(struct Philosopher *philos)
{
    int     i;
    int     finished_eating;

    i = 0;
    finished_eating = 0;
    if (philos->diner_infos->nb_of_meals == NO_MEAL_LIMIT)
        return (0);
    while (i < philos->diner_infos->nb_of_philos)
    {
        pthread_mutex_lock(&philos->diner_infos->meal_lock);
        if (philos[i].meal_counter == philos->diner_infos->nb_of_meals)
            finished_eating++;
        pthread_mutex_unlock(&philos->diner_infos->meal_lock);
        i++;
    }
    if (finished_eating == philos->diner_infos->nb_of_philos)
    {
        pthread_mutex_lock(&philos->diner_infos->dead_lock);
        *philos->dead = 1;
        pthread_mutex_unlock(&philos->diner_infos->dead_lock);
        printf("TOUT LE MONDE A FINI DE MANGER CIAO \n");
        return (1);
    }
    return (0);
}


            // END BECAUSE OF TIME 
int is_dead(struct Philosopher *philo)
{
    pthread_mutex_lock(&philo->diner_infos->meal_lock);
    if ((time_now_ms(philo->diner_infos->program_start) - philo->last_eaten > philo->diner_infos->time_to_die) && (philo->eating == 0)) // THIS 
        return(pthread_mutex_unlock(&philo->diner_infos->meal_lock), 1);
    return (pthread_mutex_unlock(&philo->diner_infos->meal_lock), 0);
}

int check_if_dead(struct Philosopher *philos)
{
    int     i;

    i = 0;
    while(i < philos->diner_infos->nb_of_philos)
    {
        if (is_dead(&philos[i]))
        {
            write_log(&philos[i], RED "died" reset);
            pthread_mutex_lock(&philos->diner_infos->dead_lock);
            *philos->dead = 1;
            pthread_mutex_unlock(&philos->diner_infos->dead_lock);
            return (1);
        }
        i++;
    }
    return (0);
}


        // MONITEUR QUI LANCE LES FONCTIONS CHECK_IF_DEAD ET EVERYONE_ATE EN BOUCLE
        // associe au thread monitor

void    *check_if_end(void *p)
{
    struct Philosopher *philo;

    philo = (struct Philosopher *)p;
    while(1)
    {
        if (check_if_dead(philo) || everyone_ate(philo))
            break;
    }
    return (p);
}