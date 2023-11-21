/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:22:16 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/21 06:44:35 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_forks(t_philo *p)
{
	sem_wait(p->sem_forks);
	sem_wait(p->sem_forks);
	print_out(p, FORK);
	return (0);
}

int eatting(t_philo *p)
{
	// if (check_dead(p))
	// {
	// 	sem_post(p->sem_forks);
	// 	sem_post(p->sem_forks);
	// 	return (1);
	// }

	p->last_meal = get_time_now();

	print_out(p, EAT);
	ft_usleep(p->time_eat);

	// sem_wait(p->sem_last_meal);
	// p->last_meal = get_time_now();
	// sem_post(p->sem_last_meal);

	sem_post(p->sem_forks);
	sem_post(p->sem_forks);
	p->had_meal++;
	if (p->had_meal == p->must_meal)
		return (1);
	return (0);
}

int sleeping(t_philo *p)
{
	// if (check_dead(p))
	// 	return (1);
	print_out(p, SLEEP);
	ft_usleep (p->time_sleep);
	return (0);
}

int thinking(t_philo *p)
{
	// if (check_dead(p))
	// 	return (1);
	print_out(p, THINK);
	return (0);
}

int	routine(t_philo *p, int idx)
{
	// if (sem_unlink(SEM_DIE) == -1) {
	// 	perror("routine: sem_unlink");
	// 	return 1;
	// }
	sem_unlink(SEM_DIE);
	p->philo_no = idx + 1;
	// sem_wait(p->sem_last_meal);
	p->last_meal = get_time_now();
	// sem_post(p->sem_last_meal);
	if (pthread_create(&p->monitor, NULL, &monitor, p))
	{
		perror (E_THREAD_CREATE);
		exit(1);
	}
	
	if (p->philo_no % 2)
		// usleep (1000);
		usleep ((p->time_eat * 1000) - 1000);
	while (p->had_meal < p->must_meal)
	{
		if (get_forks(p) || check_dead(p))
			break ;
		if (eatting(p)|| check_dead(p))
			break ;
		if (sleeping(p)|| check_dead(p))
			break;
		if (thinking(p)|| check_dead(p))
			break;
		// if (get_forks(p))
		// 	break ;
		// if (eatting(p))
		// 	break ;
		// if (sleeping(p))
		// 	break;
		// if (thinking(p))
		// 	break;
	}
	
	if (pthread_join(p->monitor, NULL))
	{
		perror (E_THREAD_JOIN);
		exit (1);
	}
	exit (0);
}