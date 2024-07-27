/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   craete_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:58:59 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/20 15:01:41 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philos_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_nbr = 0;
		data->philos[i].last_meal = get_time();
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->philos_nbr];
		if (pthread_mutex_init(&data->philos[i].philo_lock, NULL))
			return (ft_error ("Error while mutex inisialization..."));
	}
	return (0);
}

static int	forks_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_error("Error while mutex inisialization..."));
	}
	return (0);
}

static int	data_init(t_data *data, char **av)
{
	if (ft_parsing(data, av))
		return (1);
	data->start = get_time();
	data->dead = 0;
	if (pthread_mutex_init(&data->print_lock, NULL)
		|| pthread_mutex_init(&data->data_lock, NULL))
		return (ft_error("Error while mutex inisialization..."));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_nbr);
	if (!data->forks)
		return (ft_error("Error in malloc"));
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		return (ft_error("Error in malloc"));
	if (forks_init(data) || philos_init(data))
		return (1);
	return (0);
}

int	create_philos(t_data *data, char **av)
{
	if (data_init(data, av))
		return (1);
	start_simulation(data);
	return (0);
}
