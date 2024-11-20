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
            pthread_mutex_unlock(&(fork->mutex));
            return (0);
        }
    }
    else
        return (0);
}

void    release_fork(struct Fork *fork)
{
    fork->philo_id = -1;
}