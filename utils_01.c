/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:40:16 by mdiamant          #+#    #+#             */
/*   Updated: 2023/08/31 13:27:06 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_msg_02(t_philo *philo, int msg)
{
	long long int	time;

	time = get_time() - philo->st_time;
	if (msg == EAT)
		printf("%lld %d is eating\n", time, philo->id);
	else if (msg == FORK)
		printf("%lld %d has taken a fork\n", time, philo->id);
	else if (msg == SLEEP)
		printf("%lld %d is sleeping\n", time, philo->id);
	else if (msg == THINK)
		printf("%lld %d is thinking\n", time, philo->id);
	else if (msg == DIE)
	{
		philo->data->dead++;
		printf("%lld %d died\n", time, philo->id);
	}
}

void	print_msg(t_philo *philo, int msg)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->dead > 0)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	print_msg_02(philo, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	first_and_second_fork(int *first_fork, int *second_fork, t_philo *philo)
{
	int	next;

	if (philo->id == philo->nb_philo)
		next = 0;
	else
		next = philo->id;
	if (philo->id > next)
	{
		*first_fork = next;
		*second_fork = philo->id - 1;
	}
	else
	{
		*first_fork = philo->id -1;
		*second_fork = next;
	}
}

static int	verif_arg_02(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("error: wrong type of argument\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	verif_arg(char **argv)
{
	if (verif_arg_02(argv) == 0)
		return (0);
	if (argv[1][0] == '1' && !argv[1][1])
	{
		printf("0 1 is thinking\n");
		printf("0 1 has taken a fork\n");
		ft_usleep(atoi(argv[2]));
		printf("%d ", atoi(argv[2]));
		printf("1 died\n");
		return (0);
	}
	if ((argv[1][0] == '0' && !argv[1][1]) || argv[1][0] == '-')
	{
		printf("error: wrong number of philo \n");
		return (0);
	}
	if (!ft_isdigit(argv[1]) || !ft_isdigit(argv[2]) || !ft_isdigit(argv[3])
		|| !ft_isdigit(argv[4]) || (argv[5] && !ft_isdigit(argv[5])))
	{
		printf("error: wrong type of argument\n");
		return (0);
	}
	return (1);
}
