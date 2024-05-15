/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:55:30 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/25 04:10:21 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_print(t_philo *philo, char *str)
{
	sem_wait(philo->block_printf);
	if (!philo->stop)
		printf("%lld %d %s\n", find_time() - philo->t_start, philo->index, str);
	sem_post(philo->block_printf);
}

void	*check_monitor(void *args)
{
	t_philo	*philo;

	philo = args;
	while (!philo->stop)
	{
		if (find_time() - philo->t_meal > philo->t_die)
		{
			philo->died = 1;
			print_death(philo, "died");
			philo->stop = 1;
			break ;
		}
		if (philo->num_eat != -1 && philo->num_eat_count >= philo->num_eat)
		{
			philo->stop = 1;
			break ;
		}
	}
	if (philo->died)
		exit (1);
	else
		exit (0);
}

void	exit_philo(t_philo **philo)
{
	t_philo	*data;
	int		i;
	int		status;

	data = *philo;
	i = 0;
	while (i < data->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->num_philos)
				kill(data->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(data->block_printf);
	sem_close(data->block_fork);
	sem_unlink("block_printf");
	sem_unlink("block_fork");
	free(data->pid);
	free(data);
}

void	philo_start(t_philo *philo)
{
	if (pthread_create(&philo->check_monitor, NULL, &check_monitor, philo))
		ft_error("ERROR");
	while (1)
	{
		usleep(100);
		sem_wait(philo->block_fork);
		philo_print(philo, "has taken fork");
		sem_wait(philo->block_fork);
		philo_print(philo, "has taken fork");
		philo_print(philo, "is eating");
		upgrade_sleep(philo->t_eat, philo);
		philo->t_meal = find_time();
		sem_post(philo->block_fork);
		sem_post(philo->block_fork);
		philo->num_eat_count += 1;
		philo_print(philo, "is sleeping");
		upgrade_sleep(philo->t_sleep, philo);
		philo_print(philo, "is thinking");
	}
	if (pthread_join(philo->check_monitor, NULL))
		ft_error("ERROR");
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = init_philo(ac, av);
	philo->t_start = find_time();
	while (i < philo->num_philos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == 0)
		{
			philo->index = i + 1;
			philo->t_meal = find_time();
			philo_start(philo);
		}
		i++;
	}
	exit_philo(&philo);
	sem_close(philo->block_printf);
	sem_close(philo->block_fork);
	sem_unlink("block_printf");
	sem_unlink("block_fork");
}
