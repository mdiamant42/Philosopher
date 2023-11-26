/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:37:40 by mdiamant          #+#    #+#             */
/*   Updated: 2023/08/31 13:13:33 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DIE 4

typedef struct s_data
{
	long int		st_time;
	int				nb_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				dead;
	int				nb_meals_max;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				nb_philo;
	int				status;
	int				nb_meals;
	int				nb_meals_max;
	int				is_dead;
	long int		last_meal;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		st_time;
	pthread_t		*thread;
	pthread_mutex_t	mutex_is_dead;
	pthread_mutex_t	mutex_life;
	t_data			*data;
}				t_philo;

typedef struct s_utils
{
	t_philo	**philo;
	int		nb_philo;
	int		time_to_die;
}			t_utils;

void			routine(t_philo *philo);
void			ft_usleep(long int time_in_ms);
long long int	get_time(void);
int				ft_atoi(const char *str);
t_data			*data_init(char **argv);
t_data			*data_init(char **argv);
t_philo			**philo_init(t_data *data);
pthread_mutex_t	*init_forks(t_data *data);
void			free_all(t_philo **philo, t_data *data);
void			print_msg(t_philo *philo, int msg);
void			philo_is_sleep(t_philo *philo);
void			philo_is_think(t_philo *philo);
int				philo_is_eat(t_philo *philo);
void			first_and_second_fork(int *ff, int *sf, t_philo *philo);
int				ft_isdigit(char *c);
int				verif_arg(char **argv);
void			wrass(t_philo **philo, int nb_philo);
void			ft_philo(t_philo **philo, t_utils *utils);
void			verif_dead(t_utils *utils);

#endif
