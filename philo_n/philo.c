/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:11:16 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/16 14:35:05 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_philo *p)
{
	int nb;
	int i;

	i = 0;
	nb = p[i].rule->nb;
	pthread_mutex_destroy(&p[i].rule->mutex_dead);
	while (i < nb)
	{
		pthread_mutex_destroy (&p[i].l_fork);
		pthread_mutex_destroy (&p[i].mutex_last_meal);
	}
}

int	create_thread(t_philo *p)
{
	t_rule	*rule;
	int i;

	i = 0;
	rule = p[i].rule;
	while (i < rule->nb)
	{
		if (pthread_create(&p[i].th, NULL, &routine, &p[i]))
		{
			destroy_mutex(p);
			free(p);
			ft_putendl_fd (FAILED_CREATE_THREAD, 2);
			return (1);
		}
		i++ ;
	}
	if (pthread_create(&rule->monitor_th, NULL, &monitor, p))
	{
		destroy_mutex(p);
		free(p);
		ft_putendl_fd (FAILED_CREATE_THREAD, 2);
		return (1);
	}
	return (0);
}

int join_thread(t_philo *p)
{
	t_rule	*rule;
	int i;

	i = 0;
	rule = p[i].rule;
	while (i < rule->nb)
	{
		if (pthread_join(p[i].th, NULL))
		{
			destroy_mutex(p);
			free(p);
			ft_putendl_fd (FAILED_JOIN_THREAD, 2);
			return (1);
		}
		i++ ;
	}
	if (pthread_join(rule->monitor_th, NULL))
	{
		destroy_mutex(p);
		free(p);
		ft_putendl_fd (FAILED_CREATE_THREAD, 2);
		return (1);
	}
	return (0);
}

// void debug(t_philo *p)
// {
// 	int i;
// 	int nb;

// 	i = 0;
// 	nb = p[i].rule->nb;
// 	while (i < nb)
// 	{
// 		printf ("P_%d, l: %p, r: %p\n", p[i].no, &p[i].l_fork, p[i].r_fork);
// 		i++ ;
// 	}
// }

int	main(int argc, char **argv)
{
	t_rule  rule;
	t_philo *p;

	if (init_rule(&rule, argc, argv))
		return (1);
	if (init_philos(&rule, &p))
		return (1);
	// debug(p);
	if (create_thread(p))
		return (1);
	if (join_thread(p))
		return (1);
	free (p);
	return (0);
}