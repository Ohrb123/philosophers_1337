/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_creating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:37:41 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/20 15:03:15 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_die(t_data *data)
{
	int	c;

	pthread_mutex_lock(&data->data_lock);
	c = data->dead;
	pthread_mutex_unlock(&data->data_lock);
	return (c);
}

static void	my_printf(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->print_lock);
	if (!is_die(data))
		printf("%ld\t%d\t%s\n", get_time() - data->start, id, str);
	pthread_mutex_unlock(&data->print_lock);
}

static int	ft_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	my_printf(philo->data, "has taken a fork", philo->id);
	if (philo->data->philos_nbr == 1)
	{
		my_usleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(philo->l_fork);
	my_printf(philo->data, "has taken a fork", philo->id);
	my_printf(philo->data, "is eating", philo->id);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_lock);
	philo->meals_nbr++;
	my_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

static void	*ft_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
	{
		my_printf(philo->data, "is thinking", philo->id);
		my_usleep(50, philo->data);
	}
	while (!is_die(philo->data))
	{
		if (ft_forks(philo))
			return (NULL);
		my_printf(philo->data, "is sleeping", philo->id);
		my_usleep(philo->data->time_to_sleep, philo->data);
		my_printf(philo->data, "is thinking", philo->id);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	if (pthread_create(&monitor, NULL, &dead_check, data))
		ft_error ("Error while creating a thread...");
	while (++i < data->philos_nbr)
	{
		if (pthread_create(&data->philos[i].thread, \
		NULL, &ft_routine, &data->philos[i]))
			ft_error("Error while creating a thread...");
	}
	if (pthread_join(monitor, NULL))
		ft_error("Error while joining a thread...");
	i = -1;
	while (++i < data->philos_nbr)
		if (pthread_join(data->philos[i].thread, NULL))
			ft_error("Error while joining a thread...");
	pthread_mutex_destroy(&data->data_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->philos->philo_lock);
	free(data->forks);
	free(data->philos);
}
