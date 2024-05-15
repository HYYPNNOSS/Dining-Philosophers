/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:55:59 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/25 03:59:10 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	find_args(const char *str)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
			i++;
	if (str[i] == '+')
			i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		else
		{
			num = num * 10 + (str[i] - 48);
			if (num > 2147483647)
				return (-1);
			i++;
		}	
	}
	return ((int)num);
}

static	t_philo	*init_data(int ac, char **av)
{
	t_philo	*data;

	data = malloc(sizeof(t_philo));
	if (!data)
		ft_error("ERROR");
	data->num_philos = find_args(av[1]);
	data->num_forks = data->num_philos;
	data->t_die = find_args(av[2]);
	data->t_eat = find_args(av[3]);
	data->t_sleep = find_args(av[4]);
	if (data->num_philos < 1 || data->t_die < 1
		|| data->t_eat < 1 || data->t_sleep < 1)
		ft_error("Error: Wrong arguments");
	data->num_eat = -1;
	if (ac == 6)
	{
		data->num_eat = find_args(av[5]);
		if (data->num_eat == -1)
			ft_error("Error: Wrong arguments");
	}
	data->num_eat_count = 0;
	data->stop = 0;
	data->died = 0;
	return (data);
}

t_philo	*init_philo(int ac, char **av)
{
	t_philo	*data;

	if (ac != 5 && ac != 6)
		ft_error("Error: Wrong number of arguments");
	data = init_data(ac, av);
	data->pid = malloc(sizeof(int) * data->num_forks);
	if (!data->pid)
		ft_error("ERROR");
	sem_unlink("block_printf");
	sem_unlink("block_fork");
	data->block_printf = sem_open("block_printf", O_CREAT , 0777, 1);
	data->block_fork = sem_open("block_fork", O_CREAT, 0777, data->num_forks);
	if (data->block_printf <= 0 || data->block_fork <= 0)
		ft_error("ERROR: sem_open");
	return (data);
}
