/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:57:17 by aboukezi          #+#    #+#             */
/*   Updated: 2024/11/21 21:39:34 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

static int     is_nb(char *s)
{
    int     i;
    
    i = 0;
    while (s[i])
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

int error_input(int ac, char **av)
{
    if (ac != 5 && ac != 6)
    {
        printf("Invalid input : nb_philos ms_die ms_eat ms_sleep (nb_meals)\n");
        return (1);
    }
    if (ft_strtoll(av[1]) > 200 || ft_strtoll(av[1]) <= 0 || !is_nb(av[1]))
    {
        printf("nb_philos is in [1;200]\n");
        return (1);
    }
    if (ft_strtoll(av[2]) <= 0 || ft_strtoll(av[3]) <= 0|| ft_strtoll(av[4]) <= 0
        ||!is_nb(av[2]) || !is_nb(av[3]) || !is_nb(av[4]))
    {
        printf("Times must be strictly positive integers\n");
        return (1);
    }
    if (av[5] && (ft_strtoll(av[5]) < 0 || !is_nb(av[5])))
    {
        printf("meal_nb must be a positive integer\n");
        return (1);
    }
    return (0);
}