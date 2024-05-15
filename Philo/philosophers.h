/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:58:44 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/24 21:44:50 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

/* structers */

typedef struct s_args {
	int	sleep;
	int	time_to_eat;
	int	nb_of_phl;
	int	time_to_die;
	int	m_eat;
}	t_args;

typedef struct s_phl {
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	pthread_t		philo_thread;
	long long		life_time;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_left;
	long long		last_meal;
	long long		start;
	int				got_num;
	int				the_num;

}	t_phl;

/* functions */

void		exit_err(int error);
int			ft_atoi(const char *str);
int			ft_isdigit(const char c);
int			ft_check(t_args args);
int			parse_args(int argc, char **argv, t_args *p);
void		init_phls(t_phl *philo, t_args args, int ac);
int			check_death(t_phl *philos, int num);
long long	time_passed(long long start_time);
void		destroy_all_mutexes(pthread_mutex_t *forks, int num);
void		go_routine(t_phl *philosophers, int num);
void		*routine(void *philo);
void		*ft_sleep(void *philo);
void		init_mutex(pthread_mutex_t *mutex, t_phl *philo,
				int num, pthread_mutex_t *print);
void		init_start(t_phl *philo, int num);
int			check_eat(t_phl *philo, int num);

#endif
