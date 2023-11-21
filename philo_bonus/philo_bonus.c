/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:27:58 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/20 16:10:32 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"



/* fork stage */
int	luncher(t_philo *p)
{
	int	i;
	int	id;

	i = 0;
	while (i < p->philo_nb)
	{
		id = fork();
		if (id == -1)
		{
			perror (E_FORK);
			return (1);
		}
		if (id == 0)
			routine(p, i);
		i++ ;
	}
	i = 0;
	while (i < p->philo_nb)
	{
		waitpid(0, NULL, 0);
		i++;
	}
	return (0);
}

int	clean_up(t_philo *p)
{
	sem_close(p->sem_forks);
	sem_close(p->sem_print);
	// sem_close(p->sem_last_meal);
	if (sem_unlink(SEM_DIE) == -1) {
		perror("routine: sem_unlink");
		return 1;
	}
	sem_close(p->sem_die);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	p;

	if (init_philo(argc, argv, &p))
		return (1);
	if (luncher(&p))
		return (1);
	if (clean_up(&p))
		return (1);
	// printf ("I am parent\n");
	return (0);
}
