/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:28:31 by mdiamant          #+#    #+#             */
/*   Updated: 2023/08/31 13:08:34 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
}

void	free_all(t_philo **philo, t_data *data)
{
	int	i;

	i = data->nb_philo - 1;
	ft_destroy_mutex(data);
	while (i >= 0)
	{
		pthread_mutex_destroy(&philo[i]->mutex_is_dead);
		pthread_mutex_destroy(&philo[i]->mutex_life);
		free(philo[i]->thread);
		free(philo[i]);
		i--;
	}
	free(data->forks);
	free(data);
	free(philo);
}
