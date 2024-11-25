/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaen <aelaen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:57:15 by aboukezi          #+#    #+#             */
/*   Updated: 2024/11/23 12:44:21 by aelaen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
 #define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/types.h> 
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "colors.h"
# define NO_MEAL_LIMIT -65
# define USE_USLEEP 0

typedef long long TimeMs;

enum State{
    EATING,
    SLEEPING,
    THINKING,
    DEAD    
};

struct Diner{
        // struct args *input;
        int     nb_of_philos;
        int     time_to_die;
        int     time_to_eat;
        int     time_to_sleep;
        int     nb_of_meals;
        TimeMs  program_start;
        // int     sb_is_dead;
        // int     dead_philo_id;
        // int     all_ate;
        pthread_mutex_t log_mutex;
        int     dead_flag;
        // pthread_mutex_t is_dead_mutex;
        // pthread_mutex_t all_ate_mutex;
        pthread_mutex_t	dead_lock; // added
	    pthread_mutex_t	meal_lock; // added
};

struct  Philosopher{
    pthread_t thread;
    struct Diner *diner_infos;
    int     index;
    int     id;
    int     meal_counter;
    int     last_eaten;
    int     eating; // added
    int     *dead; // added
    enum State      state;
    struct Fork   *left_fork;
    struct Fork   *right_fork;
};

struct  Fork{
    int     index;
    pthread_mutex_t mutex;
    int    philo_id;
};


//              INIT : 
        /*   input_check.c  */
int     error_input(int ac, char **av);
        /*   set_the_table.c  */
int     init_input(int ac, char **av, struct Diner *diner);
int     init_philos_and_forks(struct Philosopher *philos, struct Fork *forks, struct Diner *diner);
int     pthread_create_join(struct Philosopher *philos, struct Fork *forks, struct Diner *diner);
void    clean_mutex(struct Fork *forks, struct Diner *diner);

//              PHILOS' LIVES EXECUTION : actions.c
void    *start_living(void *p);
int     philosopher_sleep(struct Philosopher *p);
int     philosopher_eat(struct Philosopher *p);
int     philosopher_think(struct Philosopher *p);

void	think(struct Philosopher  *philo);
void	dream(struct Philosopher  *philo);
void	eat(struct Philosopher  *philo);

//              UTILS : utils.c
long long   ft_strtoll(char *s);
TimeMs  time_now_ms(TimeMs start_time);
void    ft_sleep_ms(TimeMs duration);
int     min(int a, int b);
void    clean_mutex(struct Fork *forks, struct Diner *diner);
void    write_log(struct Philosopher *p, char *s);

//      MONITORING : check_if_end.c 
int     check_if_dead(struct Philosopher *philos);
int     everyone_ate(struct Philosopher *philos);
void    *check_if_end(void *p);

//      FORK MANAGEMENT : forks.c
int     try_take_fork(struct Philosopher *p, struct Fork *fork);
void    release_fork(struct Fork *fork);


// adds
int     dead_loop(struct Philosopher *philo);
void				eat(struct Philosopher *philo);
void				dream(struct Philosopher *philo);
void				think(struct Philosopher *philo);

#endif
