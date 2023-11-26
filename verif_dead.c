/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:04:37 by mdiamant          #+#    #+#             */
/*   Updated: 2023/08/31 13:18:54 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	verif_dead_01(t_utils *utils, long int *l, long int *time, int i)
{
	pthread_mutex_lock(&utils->philo[i]->mutex_life);
	*l = utils->philo[i]->last_meal;
	*time = get_time() - *l;
	pthread_mutex_unlock(&utils->philo[i]->mutex_life);
}

static int	verif_dead_02(t_utils *utils, long int time, int i)
{
	if (time > utils->time_to_die)
	{
		print_msg(utils->philo[i], DIE);
		wrass(utils->philo, utils->nb_philo);
		return (1);
	}
	return (0);
}

void	verif_dead(t_utils *utils)
{
	int			i;
	int			happy_end;
	long int	time;
	long int	last_meal;

	i = -1;
	while (1)
	{
		if (++i == utils->nb_philo)
			i = 0;
		verif_dead_01(utils, &last_meal, &time, i);
		if (last_meal == -1)
		{
			happy_end++;
			if (happy_end == utils->nb_philo)
				break ;
			continue ;
		}
		happy_end = 0;
		if (verif_dead_02(utils, time, i))
			break ;
	}
	free(utils);
}

void	wrass(t_philo **philo, int nb_philo)
{
	if (nb_philo < 0)
		return ;
	while (*philo != NULL)
	{
		pthread_mutex_lock(&(*philo)->mutex_is_dead);
		(*philo)->is_dead = 1;
		pthread_mutex_unlock(&(*philo)->mutex_is_dead);
		philo++;
	}
}
