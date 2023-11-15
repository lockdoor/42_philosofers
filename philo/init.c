/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:37:19 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/14 16:44:49 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_rule(t_rule *rule, int argc, char **argv)
{
	(void) argc;
	rule->nb = atoi(argv[1]);
	rule->die = atoi(argv[2]);
	rule->eat = atoi(argv[3]);
	rule->sleep = atoi(argv[4]);
	rule->start = get_time_now();
	rule->forks = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t) * atoi(argv[1]));
	if (rule->forks == NULL)
	{
		ft_putendl_fd(MALLOC_ERROR, 2);
		return (1);
	}
	return (0);
}

int init_philos(t_rule *rule, t_philo **philos)
{
	t_philo		*p;
	int i;

	i = 0;
	p = (t_philo *) malloc (sizeof(t_philo) * rule->nb);
	if (p == NULL)
	{
		free (rule->forks);
		ft_putendl_fd(MALLOC_ERROR, 2);
		return (1);
	}
	memset(p, 0, sizeof(t_philo) * rule->nb);
	while (i < rule->nb)
	{
		p[i].rule = rule;
		p[i].l_fork = &rule->forks[i];
		p[i].r_fork = &rule->forks[(i + 1) % rule->nb];
		i++;
	}
	*philos = p;
	return (0);
}

int	init_mutex(t_rule *rule, t_philo *philo)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = rule->forks;
	while (i < rule->nb)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			free (forks);
			free (philo);
			ft_putendl_fd("Failed on init mutex", 2);
			return (1);
		}
		i++ ;
	}
	return (0);
}

int create_thread(t_rule *rule, t_philo *p)
{
	int	i;

	i = 0;
	while (i < rule->nb)
	{
		p[i].no = i + 1;
		if (pthread_create(&p[i].th, NULL, &routine, &p[i]))
		{
			// if fail should detact all thread 
			free (rule->forks);
			free (p);
			ft_putendl_fd("Failed on create thread", 2);
			return (1);
		}
		i++ ;
	}
	return (0);
}

int	join_thread(t_rule *rule, t_philo *p)
{
	int	i;

	i = 0;
	while (i < rule->nb)
	{
		if (pthread_join(p[i].th, NULL))
		{
			free (rule->forks);
			free (p);
			ft_putendl_fd("Failed on join thread", 2);
			return (1);
		}
		i++ ;
	}
	return (0);
}
