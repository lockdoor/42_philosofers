/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:53:27 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/14 17:16:33 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	print_out(u_int64_t start, int philo, char *s)
// {
// 	u_int64_t now;


// void	*routine(void *arg)
// {
// 	t_philo *p = (t_philo *) arg;
// 	int i = p->no;
// 	u_int64_t	now;
// 	printf ("philo %d\n", i);
// 	if (i % 2 == 0)
// 		usleep (p->rule->eat / 2 * 1000);
// 	for (int j = 0; j < 4; j++){
		
// 		pthread_mutex_lock(&mutex_forks[i]);
// 		print_out(p->rule->start, i + 1, FORK);
		
// 		pthread_mutex_lock(&mutex_forks[(i + 1) % PH]);
// 		print_out(p->rule->start, i + 1, FORK);
		
// 		u_int64_t last_meal = p->last_meal;
// 		now = get_time_now();
// 		if (now - last_meal > p->rule->die && last_meal != 0)
// 		{
// 			printf ("%llu %d %s\n", now - p->rule->start, i + 1, DIE);
// 			break ;
// 		}
// 		print_out(p->rule->start, i + 1, EAT);
// 		usleep (p->rule->eat * 1000);
// 		p->last_meal = get_time_now();
		
// 		pthread_mutex_unlock(&mutex_forks[i]);
// 		pthread_mutex_unlock(&mutex_forks[(i + 1) % PH]);

// 		print_out(p->rule->start, i + 1, SLEEP);
// 		usleep (p->rule->sleep * 1000);
// 	}
// 	return (arg);
// }
void	print_out(t_philo *p, u_int64_t now, char *s)
{
	printf ("%llu %d %s\n", now - p->rule->start, p->no, s);
}

/* should check each ms wheater philo die */
void	get_forks(t_philo *p)
{
	// u_int64_t	new;
	for (int i = 0; 1; i++)
	{
		int res1 = pthread_mutex_lock(p->l_fork);
		int	res2 = pthread_mutex_lock(p->r_fork);
		printf ("i: %d\n", i);
		if (!res1 && !res2)
			break;		
	}
	print_out(p, get_time_now(), FORK);
}

void	put_forks(t_philo *p)
{
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	eating(t_philo *p)
{
	print_out(p, get_time_now(), EAT);
	usleep(p->rule->eat * 1000);
	p->cnt_meal++ ;
	p->last_meal = get_time_now();
}

void	sleeping(t_philo *p)
{
	print_out(p, get_time_now(), SLEEP);
	usleep(p->rule->sleep * 1000);
}

void	thinking(t_philo *p)
{
	print_out(p, get_time_now(), THINK);
}

void	*routine(void *arg)
{
	t_philo	p;

	p = *(t_philo *)arg;
	p.last_meal = get_time_now();
	if (p.no % 2 == 1)
		usleep(p.rule->eat / 2 * 1000);
	while (p.cnt_meal < 2)
	{
		if (p.rule->dead)
			break;
		get_forks(&p);
		if (p.rule->dead)
			break;
		eating (&p);
		put_forks(&p);
		if (p.rule->dead)
			break;
		sleeping (&p);
		if (p.rule->dead)
			break;
		thinking (&p);
	}
	return (NULL);
}

void	destroy_mutex(pthread_mutex_t *forks, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&forks[i]);
		i++ ;
	}
}

int	main(int argc, char **argv)
{
	t_rule		rule;
	t_philo		*philos;

	memset(&rule, 0, sizeof(t_rule));
	if (init_rule(&rule, argc, argv))
		return (1);
	if (init_philos(&rule, &philos))
		return (1);
	if (init_mutex(&rule, philos))
		return (1);
	if (create_thread(&rule, philos))
		return (1);
	if (join_thread(&rule, philos))
		return (1);
	destroy_mutex(rule.forks, rule.nb);
	free(rule.forks);
	free(philos);
	return (0);
}
