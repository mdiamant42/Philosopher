/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiamant <mdiamant@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:40:59 by mdiamant          #+#    #+#             */
/*   Updated: 2023/08/31 12:56:47 by mdiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_isdigit(char *c)
{
	while (*c != '\0')
	{
		if (*c < '0' || *c > '9')
			return (0);
		c++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long int	res;
	int			isneg;

	res = 0;
	isneg = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			isneg = -isneg;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str -48;
		str++;
	}
	if (res > 2147483647 && isneg == 1)
		return (-1);
	return ((int)res * isneg);
}

void	ft_usleep(long int time_in_ms)
{
	usleep(time_in_ms * 1000);
}

long long int	get_time(void)
{
	struct timeval	tv;
	long long int	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
