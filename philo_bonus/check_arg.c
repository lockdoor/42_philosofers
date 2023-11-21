/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 08:49:44 by pnamnil           #+#    #+#             */
/*   Updated: 2023/11/21 15:37:42 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	error_arg(char *s)
{
	ft_putendl_fd (s, 2);
	return (1);
}

static t_bool	check_not_digit(int argc, char **argv)
{
	int		i;
	char	*s;

	i = 1;
	while (i < argc)
	{
		s = argv[i];
		while (*s)
		{
			if (!ft_isdigit(*s))
				return (TRUE);
			s++ ;
		}
		i++ ;
	}
	return (FALSE);
}

int	check_arg(int argc, char **argv)
{
	int	n;

	if (argc < 5 || argc > 6)
		return (error_arg("Invalid argument"));
	if (check_not_digit(argc, argv))
		return (error_arg("Argument must only digit"));
	n = ft_atoi(argv[1]);
	if (n > 200 || n < 1)
		return (error_arg("Philosofer must have 1 - 200"));
	if (ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (error_arg("Time must greathen or equle 60"));
	return (0);
}
