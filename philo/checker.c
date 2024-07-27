/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:35:12 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/20 15:03:40 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(size_t time, t_data *data)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time && !is_die(data))
		usleep(500);
}

static int	ft_check(t_data *data)
{
	size_t	i;

	pthread_mutex_lock(&data->philos->philo_lock);
	i = get_time() - data->philos->last_meal;
	pthread_mutex_unlock(&data->philos->philo_lock);
	if (i > data->time_to_die)
		return (1);
	return (0);
}

static int	is_dead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr && !is_die(data))
	{
		if (ft_check(data))
		{
			pthread_mutex_lock(&data->data_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->data_lock);
			pthread_mutex_lock(&data->print_lock);
			printf("%ld\t%d\t%s\n", get_time() - data->start, \
			data->philos[i].id, "died");
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
	}
	return (0);
}

static int	check_all_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		pthread_mutex_lock(&data->philos->philo_lock);
		if (data->times_must_eat != -1337 && \
		data->philos[i].meals_nbr > data->times_must_eat)
		{
			pthread_mutex_lock(&data->data_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->data_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->philos->philo_lock);
		i++;
	}
	return (0);
}

void	*dead_check(void *content)
{
	t_data	*data;

	data = (t_data *)content;
	while (1)
		if (is_dead(data) || check_all_threads(data))
			break ;
	return (NULL);
}
