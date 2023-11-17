/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:11:16 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/17 18:44:24 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	exit_error(t_philo *p, char *s)
{
	int	nb;
	int	i;

	i = 0;
	nb = p[i].rule->nb;
	while (i < nb)
	{
		pthread_mutex_destroy (&p[i].l_fork);
		pthread_mutex_destroy (&p[i].mutex_last_meal);
	}
	pthread_mutex_destroy (&p[0].rule->mutex_eat_finished);
	free(p);
	ft_putendl_fd (s, 2);
	return (1);
}

static int	create_thread(t_philo *p)
{
	t_rule	*rule;
	int		i;

	i = 0;
	rule = p[i].rule;
	while (i < rule->nb)
	{
		if (pthread_create(&p[i].th, NULL, &routine, &p[i]))
			return (exit_error(p, FAILED_CREATE_THREAD));
		i++ ;
	}
	if (pthread_create(&rule->monitor_th, NULL, &monitor, p))
	{
		return (exit_error(p, FAILED_CREATE_THREAD));
	}
	return (0);
}

static int	join_thread(t_philo *p)
{
	t_rule	*rule;
	int		i;

	i = 0;
	rule = p[i].rule;
	if (pthread_join(rule->monitor_th, NULL))
	{
		return (exit_error(p, FAILED_JOIN_THREAD));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rule	rule;
	t_philo	*p;

	if (init_rule(&rule, argc, argv))
		return (1);
	if (init_philos(&rule, &p))
		return (1);
	if (create_thread(p))
		return (1);
	if (join_thread(p))
		return (1);
	free (p);
	return (0);
}
