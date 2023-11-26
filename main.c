/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:35:17 by mdiamant          #+#    #+#             */
/*   Updated: 2023/08/31 13:21:40 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_utils	*utils_init(t_philo **philo)
{
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	if (!utils)
		return (NULL);
	utils->philo = philo;
	utils->nb_philo = (*philo)->nb_philo;
	utils->time_to_die = (*philo)->time_to_die;
	return (utils);
}

void	ft_philo(t_philo **philo, t_utils *utils)
{
	t_philo		**phil2;
	pthread_t	*verif_thread;

	verif_thread = malloc(sizeof(pthread_t));
	phil2 = philo;
	if (!verif_thread || !utils)
		return ;
	while (*phil2 != NULL)
	{
		if (pthread_create((*phil2)->thread, NULL, (void *)&routine, (*phil2)))
			return ;
		phil2++;
	}
	if (pthread_create(verif_thread, NULL, (void *)&verif_dead, utils))
		return ;
	phil2 = philo;
	while (*phil2 != NULL)
	{
		if (pthread_join(*(*phil2)->thread, NULL))
			break ;
		phil2++;
	}
	if (pthread_join(*verif_thread, NULL))
		return ;
	free(verif_thread);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philo			**philo;
	t_utils			*utils;

	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"));
	if (verif_arg(argv) == 0)
		return (0);
	data = data_init(argv);
	philo = philo_init(data);
	utils = utils_init(philo);
	ft_philo(philo, utils);
	free_all(philo, data);
	return (0);
}
