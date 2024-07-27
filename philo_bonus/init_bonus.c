/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   craete_philos_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrb <hrb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:58:59 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/26 13:34:28 by hrb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philos_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_nbr)
	{
		sem_unlink("philo_sem");
		data->philos[i].philo_sem = \
		sem_open("philo_sem", O_CREAT | O_EXCL, 0644, 1);
		if (data->philos[i].philo_sem == SEM_FAILED)
			ft_error("ERROR while opnening data->philos->philo_sem");
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_nbr = 0;
		data->philos[i].last_meal = get_time();
	}
}

void	my_sem_init(t_data *data)
{
	sem_unlink("print_sem");
	sem_unlink("data_sem");
	sem_unlink("forks_sem");
	data->data_sem = sem_open("data_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->data_sem == SEM_FAILED)
		ft_error("ERROR while opnening data->data_sem");
	data->forks_sem = \
	sem_open("forks_sem", O_CREAT | O_EXCL, 0644, data->philos_nbr);
	if (data->forks_sem == SEM_FAILED)
		ft_error("ERROR while opnening data->forks_sem");
	data->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		ft_error("ERROR while opnening data->print_sem");
}

void	data_init(t_data *data, char **av)
{
	ft_parsing(data, av);
	data->dead = 0;
	my_sem_init(data);
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	if (!data->philos)
		ft_error("Error in malloc");
	philos_init(data);
}

void	create_philos(t_data *data, char **av)
{
	data_init(data, av);
	start_simulation(data);
}
