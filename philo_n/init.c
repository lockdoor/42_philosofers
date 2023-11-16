/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:13:31 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/16 16:06:14 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_rule(t_rule *rule, int argc, char **argv)
{
	// (void) argc;
	rule->nb = atoi(argv[1]);
	rule->die = atoi(argv[2]);
	rule->eat = atoi(argv[3]);
	rule->sleep = atoi(argv[4]);
	rule->start = get_time_now();
	rule->eat_finished = 0;
	rule->eat_nb = UINT64_MAX;
	if (argc == 6)
		rule->eat_nb = atoi(argv[5]);
	rule->dead = FALSE;
	if (pthread_mutex_init (&rule->mutex_dead, NULL)
	|| pthread_mutex_init (&rule->mutex_eat_finished, NULL))
	{
		ft_putendl_fd (FAILED_INIT_MUTEX, 2);
		return (1);
	}
	return (0);
}

void	init_r_fork(t_philo *p)
{
	int	i;
	int	nb;

	i = -1;
	nb = p[0].rule->nb;
	while (++i < nb)
		p[i].r_fork = &p[(i + 1) % nb].l_fork;
}

int	init_philos_2(t_rule *rule, t_philo *p)
{
	int i;

	i = -1;
	while (++i < rule->nb)
	{
		p[i].no = i + 1;
		p[i].rule = rule;
		if (pthread_mutex_init(&p[i].l_fork, NULL)
		|| pthread_mutex_init(&p[i].mutex_last_meal, NULL))
		{
			ft_putendl_fd (FAILED_INIT_MUTEX, 2);
			while (--i <= 0)
			{
				pthread_mutex_destroy(&p[i].l_fork);
				pthread_mutex_destroy(&p[i].mutex_last_meal);
			}
			free (p);
			return (1);
		}
	}
	init_r_fork(p);
	return (0);
}

int init_philos(t_rule *rule, t_philo **philos)
{
	t_philo	*p;
	

	p = (t_philo *) malloc (sizeof(t_philo) * rule->nb);
	if (p == NULL)
	{
		ft_putendl_fd(MALLOC_ERROR, 2);
		return (1);
	}
	memset(p, 0, sizeof(t_philo) * rule->nb);
	if (init_philos_2(rule, p))
	{
		return (1);
	}
	*philos = p;
	return (0);
}
