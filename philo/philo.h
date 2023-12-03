/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:55:17 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/03 11:16:13 by pnamnil          ###   ########.fr       */
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

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# define FAILED_INIT_MUTEX "Failed on init mutex"
# define FAILED_CREATE_THREAD "Failed on create thread"
# define FAILED_JOIN_THREAD "Failed on create thread"
# define MALLOC_ERROR "malloc error"

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_rule
{
	u_int64_t		die;
	u_int64_t		eat;
	u_int64_t		sleep;
	u_int64_t		start;
	u_int64_t		must_meal;
	int				eat_finished;
	pthread_mutex_t	mutex_eat_finished;
	pthread_mutex_t	mutex_mornitor_end;
	t_bool			monitor_end;
	int				nb;
	pthread_t		monitor_th;
}	t_rule;

typedef struct s_philo
{
	u_int64_t		last_meal;
	u_int64_t		had_meal;
	int				no;
	struct s_rule	*rule;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	pthread_t		th;
}	t_philo;

// time_utils.c
u_int64_t	get_time_now(void);
void		ft_usleep(u_int64_t ms);

// utils.c
void		ft_putendl_fd(char *s, int fd);
void		print_out(t_philo *p, char *s);
int			ft_isdigit(char c);
int			ft_atoi(const char *str);

// init.c
int			init_rule(t_rule *rule, int argc, char **argv);
int			init_philos(t_rule *rule, t_philo **philos);

// routine.c
void		*routine(void *arg);

// monitor.c
void		*monitor(void *arg);

// check_arg.c
int			check_arg(int argc, char **argv);

#endif