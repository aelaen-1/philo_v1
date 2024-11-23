/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:56:56 by aboukezi          #+#    #+#             */
/*   Updated: 2024/11/23 11:58:16 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static void clean_mutex(struct Fork *forks, struct Diner *diner)
{
    int     i;

    i = 0;
    while(i < diner->nb_of_philos)
    {
        pthread_mutex_destroy(&forks[i].mutex);
        i++;
    }
}


int main (int ac, char **av)
{
    struct Philosopher  *philos;
    struct Fork        *forks;
    struct Diner diner;
    
    if (error_input(ac, av))
        return (0);
    init_input(ac, av, &diner);
    philos = malloc(sizeof(struct Philosopher) * diner.nb_of_philos);
    forks = malloc(sizeof(struct Fork) * diner.nb_of_philos);
    init_philos_and_forks(philos, forks, &diner);
    join_threads(philos, &diner);
    clean_mutex(forks, &diner);
    free(forks);
    free(philos);
    return (0);
}