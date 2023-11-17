/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:54:29 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/17 18:17:27 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	printf ("%llu %d %s\n", now - p->rule->start, p->no, s);
}
