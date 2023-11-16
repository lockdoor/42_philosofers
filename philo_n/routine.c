/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:34:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/16 14:25:30 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void ft_usleep(u_int32_t ms)
// {
// 	u_int32_t	t;
// 	u_int32_t	u;

// 	t = 0;
// 	u = ms * 1000;
// 	while (t < u)
// 	{
// 		t += 500;
// 		usleep(500);
// 	}
// }
// int	check_dead(t_philo *p)
// {
// 	ptred
// }

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
	usleep(p->rule->eat * 1000);
	pthread_mutex_lock(&p->mutex_last_meal);
	p->last_meal = get_time_now();
	pthread_mutex_unlock(&p->mutex_last_meal);
	// ft_usleep(p->rule->eat);
	return (0);
}

int	sleeping(t_philo *p)
{
	print_out(p, SLEEP);
	usleep(p->rule->sleep * 1000);
	// ft_usleep(p->rule->sleep);
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
	int		i;

	p = (t_philo *) arg;
	i = 0;
	pthread_mutex_lock(&p->mutex_last_meal);
	p->last_meal = get_time_now();
	pthread_mutex_unlock(&p->mutex_last_meal);
	while (i < 3)
	{
		get_forks(p);
		eating(p);
		put_forks(p);
		sleeping(p);
		thinking(p);
		i++ ;
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*p;
	t_rule	*rule;
	int		i;
	u_int64_t	now;

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
				print_out(p, DIE);
				pthread_mutex_lock(&rule->mutex_dead);
				rule->dead = TRUE;
				pthread_mutex_unlock(&rule->mutex_dead);
				i = -1;
				break ;
			}
			pthread_mutex_unlock(&p[i].mutex_last_meal);
			i++ ;
		}
		if (i == -1)
			break;
	}
	return (NULL);
}
