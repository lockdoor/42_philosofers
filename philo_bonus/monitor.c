/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 06:11:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/21 06:40:21 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_dead(t_philo *p)
{
	// sem_unlink(SEM_DIE);
	p->sem_die = sem_open(SEM_DIE, AT_EACCESS, 0);
	// p->sem_die = sem_open(SEM_DIE, O_CREAT | O_EXCL, 0644, 0);
	
	if (p->sem_die == SEM_FAILED)
	{
		// if (errno == EEXIST)
		// {
			// sem_unlink(SEM_DIE);
			// perror ("some on die\n");
		// 	return (1);	
		// }
		// sem_unlink(SEM_DIE);
		// perror ("fail open_sam in check_dead");
		return (0);
	}
	// if (sem_unlink(SEM_DIE) == -1) {
	// 	perror("sem_unlink");
	// 	return 1;
	// }
	sem_close(p->sem_die);
	return (1);
}

void	*monitor(void *arg)
{
	uint64_t	now;
	t_philo		*p;

	p = (t_philo *) arg;
	usleep(100);
	while (1)
	{
		if (check_dead(p))
		{
			// perror ("from mornotor check die");
			break;
		}
		now = get_time_now();
		if (now - p->last_meal > (u_int64_t)p->time_die)
		{
			sem_wait(p->sem_print);
			if (!check_dead(p))
			{
				printf ("%llu %d %s\n", now - p->time_start, p->philo_no, DIE);
				p->sem_die = sem_open(SEM_DIE, O_CREAT | O_EXCL, 0644, 0);				
			}
			sem_post(p->sem_print);
			break;
		}
		usleep (1);
	}
	return (NULL);
}