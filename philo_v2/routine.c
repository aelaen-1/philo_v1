#include "include/philo.h"

void	think(struct Philosopher  *philo)
{
	write_log(philo, GRN "is thinking");
}

// Dream routine funtion

void	dream(struct Philosopher  *philo)
{
	// print_message("is sleeping", philo, philo->id);
    write_log(philo, WHT "is sleeping"reset);
	ft_sleep_ms(philo->diner_infos->time_to_sleep); // instead of ft_usleep ??
}

// Eat routine funtion

void	eat(struct Philosopher  *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	write_log(philo, CYN "has taken a fork" reset);
	if (philo->diner_infos->nb_of_philos == 1)
	{
		ft_sleep_ms(philo->diner_infos->time_to_die);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return ;
	}
	pthread_mutex_lock(&philo->left_fork->mutex);
	write_log(philo, CYN "has taken a fork" reset);
	philo->eating = 1;
	write_log(philo, MAG "is eating" reset);
	pthread_mutex_lock(&philo->diner_infos->meal_lock);
	philo->last_eaten = time_now_ms(philo->diner_infos->program_start);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->diner_infos->meal_lock);
	ft_sleep_ms(philo->diner_infos->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

int dead_loop(struct Philosopher *philo)
{
    pthread_mutex_lock(&philo->diner_infos->meal_lock);
    if (*philo->dead == 1)
		return (pthread_mutex_unlock(&philo->diner_infos->meal_lock), 1);
    pthread_mutex_unlock(&philo->diner_infos->meal_lock);
	return (0);
}


void    *start_living(void *p)
{
    struct Philosopher *myself = (struct Philosopher *)p;

    if ((myself->id % 2) == 0)
        usleep(500);
    while (!dead_loop(myself))
    {
        eat(myself);
        dream(myself);
        think(myself);
    }
    return (0); // p ? 
}
