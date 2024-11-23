#include "include/philo.h"

int check_if_dead(struct Philosopher *p)
{
    if (p->diner_infos->sb_is_dead)
        return (1);
    if (time_now_ms(p->diner_infos->program_start) - p->last_eaten >= p->diner_infos->time_to_die)
    {
        if (!pthread_mutex_lock(&p->diner_infos->is_dead_mutex) && !(p->diner_infos->sb_is_dead))
        {
            p->diner_infos->dead_philo_id = p->id;
            p->diner_infos->sb_is_dead = 1;
        }
        pthread_mutex_unlock(&p->diner_infos->is_dead_mutex);
        return (1);
    }
    return (0);
}

int     everyone_ate(struct Diner *diner)
{
    if (diner->nb_of_meals == NO_MEAL_LIMIT)
        return (0);
    if (diner->all_ate == (diner->nb_of_philos * diner->nb_of_meals))
        return (1);
    return (0);
}