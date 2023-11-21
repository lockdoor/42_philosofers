/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:28:46 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/21 06:27:36 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>

# define E_FORK "Failed on fork"
# define E_SEM_OPEN "Failed on sem_open"
# define E_SEM_UNLINK "Failed on sem_unlink"
# define E_THREAD_CREATE "Failed on create thread"
# define E_THREAD_JOIN "Failed on join thread"
# define E_MUTEX_INIT "Failed on mutex init"
# define E_MUTEX_DEST "Failed on mutex destroy"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_DIE "/sem_die"
# define SEM_LAST_MEAL "/sem_last_meal"

typedef struct s_philo
{
	int	philo_nb;
	int philo_no;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int die_status;
	u_int64_t time_start;
	u_int64_t must_meal;
	u_int64_t had_meal;
	u_int64_t last_meal;
	sem_t	*sem_forks;
	sem_t	*sem_print;
	sem_t	*sem_die;
	pthread_t	monitor;
	sem_t *sem_last_meal;
}	t_philo;

// init_philo.c
int	init_philo(int argc, char **argv, t_philo *p);

// routine.c
int	routine(t_philo *p, int idx);

// monitor.c
void	*monitor(void *arg);
int	check_dead(t_philo *p);

// utils.c
int	ft_atoi(const char *str);
void	print_out(t_philo *p, char *s);

// time_utils.c
u_int64_t	get_time_now(void);
void	ft_usleep(u_int64_t ms);

#endif