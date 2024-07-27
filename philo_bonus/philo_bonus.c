/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:00:52 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/20 15:00:07 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
		create_philos(&data, av);
	else
		ft_error("The number of arguments is incorrect!");
	return (0);
}
