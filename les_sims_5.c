/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_sims_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:42:48 by mdiamant          #+#    #+#             */
/*   Updated: 2023/09/14 16:03:47 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_die / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex_is_dead);
		if (philo->is_dead)
		{
			pthread_mutex_unlock(&philo->mutex_is_dead);
			philo->status = DIE;
			break ;
		}
		pthread_mutex_unlock(&philo->mutex_is_dead);
		if (philo_is_eat(philo))
			break ;
		philo_is_sleep(philo);
		philo_is_think(philo);
	}
	pthread_mutex_lock(&philo->mutex_life);
	philo->last_meal = -1;
	pthread_mutex_unlock(&philo->mutex_life);
}

void	philo_is_sleep(t_philo *philo)
{
	philo->status = SLEEP;
	print_msg(philo, SLEEP);
	ft_usleep(philo->time_to_sleep);
}

void	philo_is_think(t_philo *philo)
{
	int	thk;

	thk = philo->time_to_die - philo->time_to_sleep - philo->time_to_eat;
	philo->status = THINK;
	print_msg(philo, THINK);
	if (thk < 10)
		return ;
	ft_usleep(thk - 10);
}

int	philo_is_eat(t_philo *philo)
{
	int	first_f;
	int	second_f;
	int	return_value;

	return_value = 0;
	first_and_second_fork(&first_f, &second_f, philo);
	pthread_mutex_lock(&philo->data->forks[first_f]);
	print_msg(philo, FORK);
	pthread_mutex_lock(&philo->data->forks[second_f]);
	print_msg(philo, FORK);
	philo->status = EAT;
	print_msg(philo, EAT);
	pthread_mutex_lock(&philo->mutex_life);
	philo->nb_meals++;
	philo->last_meal = get_time();
	if (philo->nb_meals == philo->nb_meals_max)
		return_value = 1;
	pthread_mutex_unlock(&philo->mutex_life);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[first_f]);
	pthread_mutex_unlock(&philo->data->forks[second_f]);
	return (return_value);
}
