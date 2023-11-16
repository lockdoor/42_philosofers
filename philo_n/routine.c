/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:34:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/16 16:15:25 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(u_int64_t ms)
{
	u_int64_t	start;
	u_int64_t	now;

	start = get_time_now();
	now = start;
	while (now - start < ms)
	{
		usleep(1);
		now = get_time_now();
	}
}

void	print_out(t_philo *p, char *s)
{
	u_int64_t	now;

	now = get_time_now();
	printf ("%llu %d %s\n", now - p->rule->start, p->no, s);
}

int	get_forks(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	pthread_mutex_lock(p->r_fork);
	print_out(p, FORK);
	return (0);
}

void	put_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

int	eating(t_philo *p)
{
	print_out(p, EAT);
	// usleep(p->rule->eat * 1000);
	ft_usleep(p->rule->eat);
	pthread_mutex_lock(&p->mutex_last_meal);
	p->last_meal = get_time_now();
	pthread_mutex_unlock(&p->mutex_last_meal);
	return (0);
}

int	sleeping(t_philo *p)
{
	print_out(p, SLEEP);
	// usleep(p->rule->sleep * 1000);
	ft_usleep(p->rule->sleep);
	return (0);
}

int	thinking(t_philo *p)
{
	print_out(p, THINK);
	return (0);
}

void	*routine(void *arg)
{
	t_philo *p;
	u_int64_t		i;

	p = (t_philo *) arg;
	i = 0;
	pthread_mutex_lock(&p->mutex_last_meal);
	p->last_meal = get_time_now();
	pthread_mutex_unlock(&p->mutex_last_meal);
	while (i < p->rule->eat_nb)
	{
		get_forks(p);
		eating(p);
		put_forks(p);
		sleeping(p);
		thinking(p);
		i++ ;
	}
	pthread_mutex_lock(&p->rule->mutex_eat_finished);
	p->rule->eat_finished += 1 ;
	pthread_mutex_unlock(&p->rule->mutex_eat_finished);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*p;
	t_rule	*rule;
	int	i;
	u_int64_t	now;
	// t_bool		end;

	p = (t_philo *) arg;
	rule = p[0].rule;
	while (TRUE)
	{
		i = 0;
		while (i < rule->nb)
		{
			pthread_mutex_lock(&p[i].mutex_last_meal);
			now = get_time_now();
			if (now - p[i].last_meal > rule->die)
			{
				pthread_mutex_lock(&rule->mutex_dead);
				rule->dead = TRUE;
				print_out(p, DIE);
				pthread_mutex_unlock(&rule->mutex_dead);
				rule->monitor_end = TRUE;
				break ;
			}
			pthread_mutex_unlock(&p[i].mutex_last_meal);
			pthread_mutex_lock(&rule->mutex_eat_finished);
			if (rule->eat_finished == rule->nb)
			{
				rule->monitor_end = TRUE;
				break;
			}
			pthread_mutex_unlock(&rule->mutex_eat_finished);
			i++ ;
		}
		if (rule->monitor_end == TRUE)
			break;
	}
	return (NULL);
}
