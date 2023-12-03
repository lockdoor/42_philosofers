/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:34:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/03 11:41:50 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_forks(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	pthread_mutex_lock(p->r_fork);
	print_out(p, FORK);
	return (0);
}

static int	eating(t_philo *p)
{
	print_out(p, EAT);
	ft_usleep(p->rule->eat);
	pthread_mutex_lock(&p->mutex_last_meal);
	p->last_meal = get_time_now();
	pthread_mutex_unlock(&p->mutex_last_meal);
	p->had_meal++ ;
	if (p->had_meal == p->rule->must_meal)
	{
		pthread_mutex_lock(&p->rule->mutex_eat_finished);
		p->rule->eat_finished += 1;
		pthread_mutex_unlock(&p->rule->mutex_eat_finished);
		pthread_mutex_unlock(&p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		return (1);
	}
	pthread_mutex_unlock(&p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	return (0);
}

static int	sleeping(t_philo *p)
{
	print_out(p, SLEEP);
	ft_usleep(p->rule->sleep);
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *) arg;
	p->had_meal = 0;
	pthread_mutex_lock(&p->mutex_last_meal);
	p->last_meal = get_time_now();
	pthread_mutex_unlock(&p->mutex_last_meal);
	if (p->no % 2 == 0)
		usleep(p->rule->eat / 2);
	while (p->had_meal < p->rule->must_meal)
	{
		get_forks(p);
		if (eating(p))
			break ;
		sleeping(p);
		print_out(p, THINK);
	}
	return (NULL);
}
