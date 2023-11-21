/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:37:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/21 15:45:00 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_sem_open(t_philo *p)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MONITOR);
	p->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, p->philo_nb);
	if (p->sem_forks == SEM_FAILED)
	{
		perror (E_SEM_OPEN);
		return (1);
	}
	p->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (p->sem_print == SEM_FAILED)
	{
		perror (E_SEM_OPEN);
		return (1);
	}
	p->sem_monitor = sem_open(SEM_MONITOR, O_CREAT | O_EXCL, 0644, 1);
	if (p->sem_monitor == SEM_FAILED)
	{
		perror (E_SEM_OPEN);
		return (1);
	}
	return (0);
}

static int	ft_sem_unlink(void)
{
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
	if (sem_unlink(SEM_MONITOR))
	{
		perror(E_SEM_UNLINK);
		return (1);
	}
	sem_unlink(SEM_DIE);
	return (0);
}

// hard code for philo has only one
static int	check_philo_only_one(t_philo *p)
{
	if (p->philo_nb == 1)
	{
		ft_usleep(p->time_die);
		printf ("%d %d %s\n", p->time_die, 1, DIE);
		return (1);
	}
	return (0);
}

int	init_philo(int argc, char **argv, t_philo *p)
{
	memset(p, 0, sizeof(t_philo));
	p->philo_nb = ft_atoi(argv[1]);
	p->time_die = ft_atoi(argv[2]);
	p->time_eat = ft_atoi(argv[3]);
	p->time_sleep = ft_atoi(argv[4]);
	if (check_philo_only_one(p))
		return (1);
	p->must_meal = SIZE_MAX;
	if (argc == 6)
		p->must_meal = ft_atoi(argv[5]);
	p->had_meal = 0;
	if (ft_sem_open(p))
		return (1);
	if (ft_sem_unlink())
		return (1);
	p->time_start = get_time_now();
	return (0);
}
