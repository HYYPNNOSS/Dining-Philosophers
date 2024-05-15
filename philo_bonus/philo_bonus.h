/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 03:55:28 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/25 03:59:33 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "semaphore.h"
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_philo
{
	int				num_philos;
	int				num_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	int				num_eat_count;
	int				stop;
	int				died;
	int				*pid;
	sem_t			*block_printf;
	sem_t			*block_fork;
	long long int	t_start;
	int				index;
	long long int	t_meal;
	pthread_t		check_monitor;
}t_philo;

t_philo		*init_philo(int argc, char **argv);
int			ft_error(char *str);
int			ft_isdigit(int c);
long long	find_time(void);
void		upgrade_sleep(long long time, t_philo *data);
void		print_death(t_philo *philo, char *str);
#endif