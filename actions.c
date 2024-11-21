#include "include/philo.h"

static void ft_write_log(struct Philosopher *p, char *s)
{
    if (!pthread_mutex_lock(&p->diner_infos->log_mutex))
    {
        printf("%lld %d %s\n", time_now_ms(p->diner_infos->program_start), p->id, s);
        pthread_mutex_unlock(&p->diner_infos->log_mutex);
        return ;
    }
    else
        ft_write_log(p, s);
}

int    philosopher_eat(struct Philosopher *p)
{
    p->last_eaten = time_now_ms(p->diner_infos->program_start);
    p->state = EATING;
    p->meal_counter += 1;
    ft_write_log(p, MAG "is eating");
    usleep(min(p->diner_infos->time_to_eat, p->diner_infos->time_to_eat) * 1000);
    release_fork(p->left_fork);
    release_fork(p->right_fork);
    return (1);
}

int    philosopher_sleep(struct Philosopher *p)
{
    p->state = SLEEPING;
    ft_write_log(p, WHT "is sleeping");
    usleep(min(p->diner_infos->time_to_die, p->diner_infos->time_to_sleep) * 1000);
    return (1);
}

int    philosopher_think(struct Philosopher *p)
{
    if (p->state != THINKING)
    {
        ft_write_log(p, GRN "is thinking");
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

static int  live_once(struct Philosopher *myself)
{
    if (philosopher_think(myself) && check_if_dead(myself))
        return (1);
    if (try_take_fork(myself, myself->left_fork))
    {
        if(check_if_dead(myself))
                return (1) ;
        if (try_take_fork(myself, myself->right_fork))
        {
            if (philosopher_eat(myself) && check_if_dead(myself))
                return (1) ;
            if (philosopher_sleep(myself) && check_if_dead(myself))
                return (1) ;
        }
        else
        {
            release_fork(myself->left_fork);
            usleep(1000);
            if(check_if_dead(myself))
                return (1) ;
        }
    }
    return (0);
}

void    *start_living(void *p)
{
    struct Philosopher *myself = (struct Philosopher *)p;

    while (!myself->diner_infos->sb_is_dead && ((myself->meal_counter < myself->diner_infos->nb_of_meals) || myself->diner_infos->nb_of_meals == NO_MEAL_LIMIT))
    {
        if (live_once(myself))
            break ;
    }
    if (myself->diner_infos->sb_is_dead && (myself->diner_infos->dead_philo_id == myself->id))
        ft_write_log(p, BHRED "died");
    return (0);
}