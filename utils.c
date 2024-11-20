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

void    join_threads(struct Philosopher *philos, struct Diner *diner)
{
    int     i;
    
    i = 0;
    while(i < diner->nb_of_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
}