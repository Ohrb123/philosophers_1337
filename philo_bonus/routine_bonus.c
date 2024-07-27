/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_creating_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrb <hrb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:37:41 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/26 14:09:24 by hrb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_printf(t_philo *philo, char *str)
{
	sem_wait(philo->data->print_sem);
	printf("%ld\t%d\t%s\n", get_time() - philo->data->start, philo->id, str);
	sem_post(philo->data->print_sem);
}

static int	ft_forks(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	my_printf(philo, "has taken a fork");
	if (philo->data->philos_nbr == 1)
	{
		my_usleep(philo->data->time_to_die);
		sem_wait(philo->data->print_sem);
		printf("%ld\t%d\t%s\n", get_time() - philo->data->start, \
		philo->id, "died");
		sem_post(philo->data->forks_sem);
		exit(30);
	}
	sem_wait(philo->data->forks_sem);
	my_printf(philo, "has taken a fork");
	my_printf(philo, "is eating");
	sem_wait(philo->philo_sem);
	philo->last_meal = get_time();
	philo->meals_nbr++;
	sem_post(philo->philo_sem);
	my_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	return (0);
}

static void	ft_routine(t_philo *philo)
{
	pthread_t	monitor;

	philo->last_meal = philo->data->start;
	if (pthread_create(&monitor, NULL, &dead_check, philo))
		ft_error ("Error while creating a thread...");
	if (pthread_detach(monitor))
		ft_error ("Error while creating a thread...");
	if (philo->id % 2 == 0)
		my_usleep(philo->data->time_to_eat);
	while (1)
	{
		if (ft_forks(philo))
			return ;
		if (philo->data->times_must_eat != -1337 && philo->meals_nbr \
		>= philo->data->times_must_eat)
			break ;
		my_printf(philo, "is sleeping");
		my_usleep(philo->data->time_to_sleep);
		my_printf(philo, "is thinking");
	}
	exit (0);
}

void	start_simulation(t_data *data)
{
	int			status;
	int			i;

	i = -1;
	data->start = get_time();
	while (++i < data->philos_nbr)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			ft_routine(&data->philos[i]);
	}
	while (1)
	{
		if (waitpid(-1, &status, WNOHANG) == -1)
			break ;
		if (WEXITSTATUS(status) == 30)
		{
			i = -1;
			while (++i < data->philos_nbr)
				kill(data->philos[i].pid, SIGKILL);
			break ;
		}
	}
	ft_close(data);
	free(data->philos);
}
