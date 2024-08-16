/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:35:12 by oelharbi          #+#    #+#             */
/*   Updated: 2024/08/16 11:20:16 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

void	*dead_check(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	while (1)
	{
		sem_wait(philo->philo_sem);
		if (get_time() - philo->last_meal > philo->data->time_to_die)
		{
			sem_wait(philo->data->print_sem);
			printf("%ld\t%d\t%s\n", get_time() - philo->data->start, \
			philo->id, "died");
			exit(42);
		}
		sem_post(philo->philo_sem);
		usleep(1000);
	}
	return (NULL);
}
