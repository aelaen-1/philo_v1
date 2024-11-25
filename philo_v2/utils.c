/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:37:05 by aboukezi          #+#    #+#             */
/*   Updated: 2024/11/15 15:51:54 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int min(int a, int b)
{
    if (a <= b)
        return (a);
    return (b);
}

long long   ft_strtoll(char *s)
{
    if (!s)
        return (0);
    long long     res;
    int     sign;
    int     i;

    i = 0;
    res = 0;
    sign = 1;
    while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
        i++;
    while (s[i] == '+' || s[i] == '-')
    {
        if (s[i] == '-')
            sign *= -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        res = res * 10 + s[i] - 48;
        i++;
    }
    return (res * sign);
}

TimeMs  time_now_ms(TimeMs start_time)
{
    struct timeval  tv;
    long long   time_in_ms;

    gettimeofday(&tv, NULL);
    time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time_in_ms - start_time);
}

void    ft_sleep_ms(TimeMs duration)
{
    #if USE_USLEEP 
    usleep(duration * 1000);
    #else
    TimeMs start = time_now_ms(0);
    while(time_now_ms(0) - start < duration)
        usleep(500);
    #endif
}

void    write_log(struct Philosopher *p, char *s)
{
    if (!pthread_mutex_lock(&p->diner_infos->log_mutex))
    {
        if (!dead_loop(p))
            printf("%lld %d %s\n", time_now_ms(p->diner_infos->program_start), p->id, s);
        pthread_mutex_unlock(&p->diner_infos->log_mutex);
    }
}

void    clean_mutex(struct Fork *forks, struct Diner *diner)
{
    int     i;

    i = 0;
    while(i < diner->nb_of_philos)
    {
        pthread_mutex_destroy(&forks[i].mutex);
        i++;
    }
}