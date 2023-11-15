/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:55:17 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/14 16:41:37 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

#define	FORK "has taken a fork"
#define EAT	"is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE	"died"
#define MALLOC_ERROR "malloc error"

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
} t_bool;

typedef struct s_rule
{
	u_int64_t		die;
	u_int64_t		eat;
	u_int64_t		sleep;
	u_int64_t		start;
	t_bool			dead; // status to check philo died
	int				nb; // number of philosopher
	pthread_mutex_t	*forks; // malloc by nb size
}	t_rule;

typedef struct s_philo
{
	u_int64_t		last_meal; // update last meal before sleep
	int				cnt_meal; // count time for philo eat
	int				no; // order of philo
	struct s_rule	*rule;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		th;
}   t_philo;

// time_utils.c
u_int64_t	get_time_now(void);

// free.c
void	free_philo(t_philo *philos);

// utils.c
void	ft_putendl_fd(char *s, int fd);

// init.c
int init_rule(t_rule *rule, int argc, char **argv);
int init_philos(t_rule *rule, t_philo **philos);
int	init_mutex(t_rule *rule, t_philo *philo);
int create_thread(t_rule *rule, t_philo *p);
int	join_thread(t_rule *rule, t_philo *p);

void	*routine(void *arg);

#endif