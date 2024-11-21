/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:56:56 by aboukezi          #+#    #+#             */
/*   Updated: 2024/11/19 16:25:59 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main (int ac, char **av)
{
	struct Philosopher	philos[200];
	struct Fork		forks[200];
	struct Diner		diner;
    
	if (error_input(ac, av))
		return (0);
	init_diner_input(ac, av, &diner);
	init_philos_and_forks(philos, forks, &diner);
	thread_create_and_join(forks, philos, &diner);
	clean_mutex(forks, &diner);
	return (0);
}
