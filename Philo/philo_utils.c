/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:25:05 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/24 21:35:22 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_all_mutexes(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	*routine(void *philo)
{
	t_phl	*philosopher;

	philosopher = (t_phl *) philo;
	if (philosopher->id % 2)
		usleep(1000);
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(philosopher->print);
	printf("%lld ms philosopher %d has taken a fork\n",
		time_passed(philosopher->start), philosopher->id);
	pthread_mutex_unlock(philosopher->print);
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(philosopher->print);
	printf("%lld ms philosopher %d has taken a fork\n",
		time_passed(philosopher->start), philosopher->id);
	printf("%lld ms philosopher %d is eating\n",
		time_passed(philosopher->start), philosopher->id);
	pthread_mutex_unlock(philosopher->print);
	usleep(philosopher->time_to_eat * 1000);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	philosopher->last_meal = time_passed(0);
	if (philosopher->got_num)
		philosopher->the_num--;
	ft_sleep(philosopher);
	return (NULL);
}

void	*ft_sleep(void *philo)
{
	t_phl	*philosophers;

	philosophers = (t_phl *) philo;
	pthread_mutex_lock(philosophers->print);
	printf("%lld ms philosopher %d is sleeping\n",
		time_passed(philosophers->start), philosophers->id);
	pthread_mutex_unlock(philosophers->print);
	usleep(philosophers->time_to_sleep * 1000);
	pthread_mutex_lock(philosophers->print);
	printf("%lld ms philosopher %d is thinking\n",
		time_passed(philosophers->start), philosophers->id);
	pthread_mutex_unlock(philosophers->print);
	routine(philosophers);
	return (NULL);
}

void	go_routine(t_phl *philosophers, int num)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * num);
	if (!forks)
		return ;
	init_mutex(forks, philosophers, num, &print);
	i = 0;
	init_start(philosophers, num);
	while (i < num)
	{
		pthread_create(&philosophers[i].philo_thread, NULL,
			&routine, &philosophers[i]);
		i++;
	}
	if (check_death(philosophers, num))
	{
		free(forks);
		destroy_all_mutexes(forks, num);
		return ;
	}
}
