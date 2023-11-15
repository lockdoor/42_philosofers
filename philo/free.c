/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:03:02 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/14 13:17:43 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[i].rule->nb)
	{
		printf ("i: %d, nb: %d\n", i, philos[i].rule->nb);
		i++ ;
	}
}