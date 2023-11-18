/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:56:58 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/18 09:56:11 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* return time in millisecond */
u_int64_t	get_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(u_int64_t ms)
{
	u_int64_t	start;
	u_int64_t	now;

	start = get_time_now();
	now = start;
	while (now - start < ms)
	{
		usleep(300);
		now = get_time_now();
	}
}
