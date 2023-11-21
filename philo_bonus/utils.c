/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:39:39 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/21 14:27:46 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	if (!s || fd < 0)
		return ;
	len = 0;
	while (s[len])
		len++ ;
	write (fd, s, len);
	write (fd, "\n", 1);
}

void	print_out(t_philo *p, char *s)
{
	u_int64_t	now;

	now = get_time_now();
	sem_wait(p->sem_print);
	if (!check_dead(p))
		printf ("%llu %d %s\n", now - p->time_start, p->philo_no, s);
	sem_post(p->sem_print);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	unsigned long	n;
	int				sign;

	n = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++ ;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++ ;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((n >= SIZE_MAX / 10) || (n >= SIZE_MAX / 10 - (*str - '0')))
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		n = (n * 10) + (*str - '0');
		str++ ;
	}
	return (n * sign);
}
