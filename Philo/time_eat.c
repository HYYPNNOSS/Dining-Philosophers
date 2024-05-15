/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_eat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:58:21 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/24 21:40:37 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	time_passed(long long start_time)
{
	long long		elapsed_time;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	elapsed_time = (tp.tv_sec * 1000) + (tp.tv_usec / 1000) - start_time;
	return (elapsed_time);
}

int	check_eat(t_phl *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (philo[0].the_num)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check(t_args args)
{
	if (args.nb_of_phl <= 0 || args.time_to_die <= 0
		|| args.time_to_eat <= 0 || args.sleep <= 0)
	{
		exit_err(1);
		return (1);
	}
	return (0);
}

void	init_phls(t_phl *philo, t_args args, int ac)
{
	int	i;

	i = 0;
	while (i < args.nb_of_phl)
	{
		philo[i].id = i;
		philo[i].life_time = args.time_to_die;
		philo[i].time_to_eat = args.time_to_eat;
		philo[i].time_left = args.time_to_die;
		philo[i].time_to_sleep = args.sleep;
		if (ac == 6)
		{
			philo[i].got_num = 1;
			philo[i].the_num = args.m_eat;
		}
		else
			philo[i].got_num = 0;
		i++;
	}	
}

void	init_mutex(pthread_mutex_t *mutex, t_phl *philo, int num,
		pthread_mutex_t *print)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philo[i].print = print;
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		philo[i].left_fork = &mutex[i % num];
		philo[i].right_fork = &mutex[(i + 1) % num];
		i++;
	}
}
