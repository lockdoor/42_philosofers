/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mornitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:15:38 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/17 18:43:21 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_helper(t_philo *p, t_rule *rule)
{
	int			i;
	u_int64_t	now;

	i = 0;
	while (i < rule->nb)
	{
		pthread_mutex_lock(&p[i].mutex_last_meal);
		now = get_time_now();
		if (now - p[i].last_meal > rule->die)
		{
			print_out(p, DIE);
			rule->monitor_end = TRUE;
			break ;
		}
		pthread_mutex_unlock(&p[i].mutex_last_meal);
		pthread_mutex_lock(&rule->mutex_eat_finished);
		if (rule->eat_finished == rule->nb)
		{
			rule->monitor_end = TRUE;
			break ;
		}
		pthread_mutex_unlock(&rule->mutex_eat_finished);
		usleep(1);
		i++ ;
	}
}

void	*monitor(void *arg)
{
	t_philo	*p;
	t_rule	*rule;
	int		i;

	p = (t_philo *) arg;
	rule = p[0].rule;
	usleep(20);
	while (!rule->monitor_end)
	{
		monitor_helper(p, rule);
	}
	i = 0;
	while (i < rule->nb)
	{
		pthread_detach(p[i].th);
		pthread_mutex_destroy (&p[i].l_fork);
		pthread_mutex_destroy (&p[i].mutex_last_meal);
		i++;
	}
	pthread_mutex_destroy (&rule->mutex_eat_finished);
	return (NULL);
}
