#include "include/philo.h"

// int    philosopher_eat(struct Philosopher *p)
// {
//     p->last_eaten = time_now_ms(p->diner_infos->program_start);
//     p->state = EATING;
//     p->meal_counter += 1;
//     write_log(p, MAG "is eating");
//     ft_sleep_ms(min(p->diner_infos->time_to_eat, p->diner_infos->time_to_die));
//     pthread_mutex_lock(&p->diner_infos->all_ate_mutex);
//     p->diner_infos->all_ate += 1;
//     pthread_mutex_unlock(&p->diner_infos->all_ate_mutex);
//     release_fork(p->left_fork);
//     release_fork(p->right_fork);
//     return (1);
// }

// int    philosopher_sleep(struct Philosopher *p)
// {
//     p->state = SLEEPING;
//     write_log(p, WHT "is sleeping");
//     ft_sleep_ms(min(p->diner_infos->time_to_die, p->diner_infos->time_to_sleep));
//     return (1);
// }

// int    philosopher_think(struct Philosopher *p)
// {
//     if (p->state != THINKING)
//     {
//         write_log(p, GRN "is thinking");
//         p->state = THINKING;
//     }
//     return (1);
// }

// static int  live_once(struct Philosopher *myself)
// {
//     if (philosopher_think(myself) && (check_if_dead(myself) || everyone_ate(myself->diner_infos)))
//         return (1);
//     if (try_take_fork(myself, myself->left_fork))
//     {
//         if(check_if_dead(myself))
//                 return (1) ;
//         if (try_take_fork(myself, myself->right_fork))
//         {
//             if (philosopher_eat(myself) && ((check_if_dead(myself)) || everyone_ate(myself->diner_infos)))
//                 return (1) ;
//             if (philosopher_sleep(myself) && ((check_if_dead(myself)) || everyone_ate(myself->diner_infos)))
//                 return (1) ;
//         }
//     }
//     return (0);
// }


// static void swap_forks(struct Fork **fork1, struct Fork **fork2)
// {
//     struct Fork *tmp;
//     tmp = *fork1;
//     *fork1 = *fork2;
//     *fork2 = tmp;
// }

// void    *start_living(void *p)
// {
//     struct Philosopher *myself = (struct Philosopher *)p;

//     if (myself->id == myself->diner_infos->nb_of_philos)
//         swap_forks(&myself->left_fork, &myself->right_fork);
//     if ((myself->id % 2) == 1)
//         usleep(500);
//     while (!myself->diner_infos->sb_is_dead && ((myself->meal_counter < myself->diner_infos->nb_of_meals) || myself->diner_infos->nb_of_meals == NO_MEAL_LIMIT))
//     {
//         if (live_once(myself))
//             break ;
//     }
//     if (myself->diner_infos->sb_is_dead && (myself->diner_infos->dead_philo_id == myself->id))
//         write_log(p, BHRED "died");
//     return (0);
// }


