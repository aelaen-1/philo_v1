#include "include/philo.h"

int try_take_fork(struct Philosopher *p, struct Fork *fork)
{
    if (!pthread_mutex_lock(&(fork->mutex)))
    {
        if (fork->philo_id == -1)
        {
            fork->philo_id = p->id;
            printf(CYN "%lld %d has taken a fork\n", time_now_ms(p->diner_infos->program_start), p->id);
            pthread_mutex_unlock(&(fork->mutex));
            return (1);
        }
        else
        {
            int res = fork->philo_id == p->id;
            pthread_mutex_unlock(&(fork->mutex));
            return (res);
        }
    }
    else
        return (0);
}

// int take_fork(struct Philosopher *p, struct Fork *fork)
// {
//     pthread_mutex_lock(&fork->mutex);
//     printf(CYN "%lld %d has taken a fork\n", time_now_ms(p->diner_infos->program_start), p->id);
//     // pthread_mutex_unlock(&(fork->mutex));
//     return (1);
// }

// void    release_fork(struct Fork *fork)
// {
//     pthread_mutex_unlock(&fork->mutex);
// }


void    release_fork(struct Fork *fork)
{
    fork->philo_id = -1;
}