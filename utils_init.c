/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:32:34 by mdiamant          #+#    #+#             */
/*   Updated: 2023/08/31 08:26:42 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_data	*data_init(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_meals_max = -1;
	if (argv[5])
		data->nb_meals_max = ft_atoi(argv[5]);
	data->dead = 0;
	data->st_time = get_time();
	data->forks = init_forks(data);
	pthread_mutex_init(&data->print, NULL);
	return (data);
}

static int	philo_init_02(t_philo *philo)
{
	philo->nb_meals = 0;
	philo->status = THINK;
	philo->is_dead = 0;
	philo->last_meal = get_time();
	pthread_mutex_init(&philo->mutex_life, NULL);
	pthread_mutex_init(&philo->mutex_is_dead, NULL);
	philo->thread = malloc(sizeof(pthread_t));
	if (!philo->thread)
		return (0);
	return (1);
}

t_philo	**philo_init(t_data *data)
{
	int			i;
	t_philo		**philo;

	philo = (t_philo **)malloc(sizeof(t_philo *) * (data->nb_philo + 1));
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->id = i + 1;
		philo[i]->nb_philo = data->nb_philo;
		philo[i]->nb_meals_max = data->nb_meals_max;
		philo[i]->time_to_die = data->time_to_die;
		philo[i]->time_to_eat = data->time_to_eat;
		philo[i]->time_to_sleep = data->time_to_sleep;
		philo[i]->st_time = data->st_time;
		philo[i]->data = data;
		if (!philo_init_02(philo[i]))
			return (NULL);
	}
	philo[i] = NULL;
	return (philo);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

// t_verif_dead **tvd_init(t_philo **philo, int nb_philo, int nb_meals_max)
// {
// 	t_verif_dead	**tvd;
// 	int				i;

// 	tvd = malloc(sizeof(t_verif_dead *) * (nb_philo + 1));
// 	if (!tvd)
// 		return (NULL);
// 	i = -1;
// 	while (++i < nb_philo)
// 	{
// 		tvd[i] = malloc(sizeof(t_verif_dead));
// 		if (!tvd[i])
// 			return (NULL);
// 		tvd[i]->philo = philo[i];
// 		tvd[i]->philo_id = philo[i]->id;
// 		tvd[i]->time_to_die = philo[i]->time_to_die;
// 		tvd[i]->time_to_eat = philo[i]->time_to_eat;
// 		tvd[i]->time_to_sleep = philo[i]->time_to_sleep;
// 		tvd[i]->nb_meals_max = nb_meals_max;
// 		tvd[i]->thread_death = malloc(sizeof(pthread_t));
// 		if (!tvd[i]->thread_death)
// 			return (NULL);
// 	}
// 	tvd[i] = NULL;
// 	return (tvd);
// }

// t_const *const_init(t_data *data)
// {
// 	t_const	*constante;

// 	constante = malloc(sizeof(t_const));
// 	if (!constante)
// 		return (NULL);
// 	constante->time_to_die = data->time_to_die;
// 	constante->time_to_eat = data->time_to_eat;
// 	constante->time_to_sleep = data->time_to_sleep;
// 	return (constante);
// }
