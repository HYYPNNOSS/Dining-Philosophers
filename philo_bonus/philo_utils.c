/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:55:53 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/25 03:58:41 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	exit(0);
}

long long	find_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

void	upgrade_sleep(long long time, t_philo *data)
{
	long long	t;

	t = find_time();
	while (!data->stop)
	{
		if (find_time() - t >= time)
			break ;
		usleep(50);
	}
}

void	print_death(t_philo *philo, char *str)
{
	sem_wait(philo->block_printf);
	if (!philo->stop)
		printf("%lld %d %s\n", \
			find_time() - philo->t_start, philo->index, str);
}
