/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 06:11:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/21 13:22:07 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_dead(t_philo *p)
{
	p->sem_die = sem_open(SEM_DIE, AT_EACCESS, 0644, 0);
	if (p->sem_die == SEM_FAILED)
		return (0);
	sem_close(p->sem_die);
	return (1);
}

static int	last_meal_check(t_philo *p)
{
	uint64_t	now;

	now = get_time_now();
	if (now - p->last_meal >= (u_int64_t)p->time_die)
	{
		sem_wait(p->sem_print);
		if (!check_dead(p))
		{
			printf ("%llu %d %s\n", now - p->time_start, p->philo_no, DIE);
			p->sem_die = sem_open(SEM_DIE, O_CREAT | O_EXCL, 0644, 0);
		}
		sem_post(p->sem_print);
		sem_post(p->sem_monitor);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo		*p;

	p = (t_philo *) arg;
	usleep(100);
	while (1)
	{
		sem_wait(p->sem_monitor);
		if (check_dead(p))
		{
			sem_post(p->sem_monitor);
			break ;
		}
		if (p->had_meal == p->must_meal)
		{
			sem_post(p->sem_monitor);
			break ;
		}
		if (last_meal_check(p))
			break ;
		sem_post(p->sem_monitor);
		usleep (100);
	}
	return (NULL);
}
