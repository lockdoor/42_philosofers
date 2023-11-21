/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:37:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/20 15:34:05 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(int argc, char **argv, t_philo *p)
{
	memset(p, 0, sizeof(t_philo));
	p->philo_nb = ft_atoi(argv[1]);
	p->time_die = ft_atoi(argv[2]);
	p->time_eat = ft_atoi(argv[3]);
	p->time_sleep = ft_atoi(argv[4]);
	p->must_meal = SIZE_MAX;
	if (argc == 6)
		p->must_meal = ft_atoi(argv[5]);
	p->had_meal = 0;

	// sem_unlink("sem_forks");
	// sem_unlink("sem_print");
	p->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, p->philo_nb);
	if (p->sem_forks == SEM_FAILED)
	{
		perror (E_SEM_OPEN);
		return (1);
	}
	p->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (p->sem_print == SEM_FAILED)
	{
		perror (E_SEM_OPEN);
		return (1);
	}
	// p->sem_last_meal = sem_open(SEM_LAST_MEAL, O_CREAT, 0644, 1);
	// if (p->sem_print == SEM_FAILED)
	// {
	// 	perror (E_SEM_OPEN);
	// 	return (1);
	// }
	
	// debug
	// if (sem_unlink(SEM_DIE))
	// {
	// 	perror("init sam_unline sam_die");
	// 	return (1);
	// }
	
	if (sem_unlink(SEM_FORKS))
	{
		perror(E_SEM_UNLINK);
		return (1);
	}
	if (sem_unlink(SEM_PRINT))
	{
		perror(E_SEM_UNLINK);
		return (1);
	}
	// if (sem_unlink(SEM_LAST_MEAL))
	// {
	// 	perror(E_SEM_UNLINK);
	// 	return (1);
	// }
	p->time_start = get_time_now();
	return (0);
}
