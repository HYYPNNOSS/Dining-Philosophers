/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hich <hel-hich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:42:08 by hel-hich          #+#    #+#             */
/*   Updated: 2022/06/24 21:37:11 by hel-hich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(int argc, char **argv, t_args *p)
{
	if (argc == 5 || argc == 6)
	{
		p->nb_of_phl = ft_atoi(argv[1]);
		p->time_to_die = ft_atoi(argv[2]);
		p->time_to_eat = ft_atoi(argv[3]);
		p->sleep = ft_atoi(argv[4]);
		if (ft_check(*p))
			return (2);
		if (argc == 6)
		{
			p->m_eat = ft_atoi(argv[5]);
			if (p->m_eat <= 0)
			{
				exit_err(1);
				return (1);
			}
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_phl	*philosophers;

	if (ac == 5 || ac == 6)
	{
		if (parse_args(ac, av, &args) == 2)
			return (1);
		philosophers = malloc(sizeof(t_phl) * args.nb_of_phl);
		if (!philosophers)
			return (0);
		init_phls(philosophers, args, ac);
		go_routine(philosophers, args.nb_of_phl);
		free(philosophers);
	}
	else if (ac < 5)
	{
		exit_err(0);
		return (1);
	}
	else
	{
		exit_err(2);
		return (1);
	}
}
