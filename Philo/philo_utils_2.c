/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 02:59:21 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/24 21:40:48 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_err(int error)
{
	if (error == 0)
		write (2, "Not Enough Arguments\n", 22);
	if (error == 1)
		write(2, "positive numbers only\n", 23);
	if (error == 2)
		write(2, "Too many arguments\n", 20);
}

int	ft_isdigit(const char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	size_t			i;
	long long		n;
	long long		sign;

	i = 0;
	n = 0;
	sign = 1;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		exit_err(1);
	return ((int)sign * (int)n);
}

int	check_death(t_phl *philos, int num)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < num)
		{
			if (philos[i % num].life_time
				< time_passed(philos[i % num].last_meal))
			{
				pthread_mutex_lock(philos[i].print);
				printf("%lld ms philosopher %d died\n",
					time_passed(philos[i % num].start), philos[i % num].id);
				return (1);
			}
			i++;
		}
		if (philos->got_num && check_eat(philos, num))
			return (1);
	}
	return (0);
}

void	init_start(t_phl *philo, int num)
{
	long long		start;
	int				i;

	i = 0;
	start = time_passed(0);
	while (i < num)
	{
		philo[i].last_meal = start;
		philo[i].start = start;
		i++;
	}
}
