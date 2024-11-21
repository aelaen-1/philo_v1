#include "include/philo.h"


int    philosopher_eat(struct Philosopher *p)
{
    pthread_mutex_lock(&p->left_fork->mutex);
    write_log(p, "\e[0;93m has taken a fork\e[0m");
    if (p->diner_infos->nb_of_philos == 1)
    {
        p->diner_infos->sb_is_dead = 1;
        p->diner_infos->dead_philo_id = 1; 
        usleep(p->diner_infos->time_to_die * 1000);
        pthread_mutex_unlock(&p->left_fork->mutex);
        return (1);
    }
    pthread_mutex_lock(&p->right_fork->mutex);
    p->last_eaten = time_now_ms(p->diner_infos->program_start);
    p->state = EATING;
    p->diner_infos->all_ate += 1;
    p->meal_counter += 1;
    write_log(p, "is \e[0;35m eating\e[0m");
    usleep(min(p->diner_infos->time_to_eat, p->diner_infos->time_to_eat) * 1000);
    pthread_mutex_unlock(&p->right_fork->mutex);
    pthread_mutex_unlock(&p->left_fork->mutex);
    return (1);
}

int    philosopher_sleep(struct Philosopher *p)
{
    p->state = SLEEPING;
    write_log(p, "is \e[0;37m sleeping\e[0m");
    usleep(min(p->diner_infos->time_to_die, p->diner_infos->time_to_sleep) * 1000);
    return (1);
}

int    philosopher_think(struct Philosopher *p)
{
    if (p->state != THINKING)
    {
        write_log(p, "is \e[0;32m thinking\e[0m");
        p->state = THINKING;
    }
    return (1);
}

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

static int  is_over(struct Philosopher *myself)
{
    if (philosopher_eat(myself) && (check_if_dead(myself) || everyone_ate(myself->diner_infos)))
        return (1);
    if (philosopher_sleep(myself) && (check_if_dead(myself) || everyone_ate(myself->diner_infos)))
        return (1);
    if (philosopher_think(myself) && (check_if_dead(myself) || everyone_ate(myself->diner_infos)))
        return (1);
    return (0);
}

void    *start_living(void *p)
{
    struct Philosopher *myself = (struct Philosopher *)p;

    if (myself->id % 2 == 0)
        usleep(1000);
    while (!myself->diner_infos->sb_is_dead && !everyone_ate(myself->diner_infos) &&((myself->meal_counter < myself->diner_infos->nb_of_meals) || myself->diner_infos->nb_of_meals == NO_MEAL_LIMIT))
    {
        if (is_over(myself))
            break ;
    }
    if (myself->diner_infos->sb_is_dead && (myself->diner_infos->dead_philo_id == myself->id))
        write_log(p, "\e[0;31m died\e[0m");
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