/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:37:41 by oelharbi          #+#    #+#             */
/*   Updated: 2024/08/17 21:59:01 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int die(t_data *data)
// {
// 	int c ;
// 	pthread_mutex_lock(&data->data_lock);
// 	c = data->dead;
// 	pthread_mutex_unlock(&data->data_lock);
// 	return (c);
// }

void	my_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld\t%d\t%s\n", get_time() - philo->data->start, philo->id, str);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (!philo->dead)
		pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_unlock(&philo->data->dead_lock);
}

static int	ft_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	my_printf(philo, "has taken a fork");
	if (philo->data->philos_nbr == 1)
	{
		my_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(philo->l_fork);
	my_printf(philo, "has taken a fork");
	my_printf(philo, "is eating");
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	if (philo->times_must_eat != -1337)
		philo->times_must_eat--;
	pthread_mutex_unlock(&philo->philo_lock);
	my_usleep(philo->data->time_to_eat);
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
		my_printf(philo, "is thinking");
		my_usleep(50);
	}
	while (philo->times_must_eat)
	{
		if (ft_forks(philo))
			return (NULL);
		my_printf(philo, "is sleeping");
		my_usleep(philo->data->time_to_sleep);
		my_printf(philo, "is thinking");
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
	{
		if (pthread_create(&data->philos[i].thread, \
		NULL, &ft_routine, &data->philos[i]))
			ft_error("Error while creating a thread...");
	}
	i = -1;
	while (++i < data->philos_nbr)
		if (pthread_detach(data->philos[i].thread))
			ft_error("Error while joining a thread...");
	is_dead(data);
	my_usleep(50);
	i =-1;
	while (++i < data->philos_nbr)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->data_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->philos->philo_lock);
	free(data->forks);
	free(data->philos);
}

int	is_dead(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->philos_nbr)
		{
			pthread_mutex_lock(&data->philos->philo_lock);
			if (get_time() - data->philos->last_meal > data->philos->data->time_to_die)
			{
				pthread_mutex_unlock(&data->philos->philo_lock);
				pthread_mutex_lock(&data->dead_lock);
				data->philos[i].dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
				if (data->philos->times_must_eat)
					my_printf(&data->philos[i], "died");
				return (1);
			}
			pthread_mutex_unlock(&data->philos->philo_lock);
		}
	}
	return (0);
}
