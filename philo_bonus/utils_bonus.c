/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:58:49 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/20 15:24:14 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close(t_data *data)
{
	int	i;

	sem_unlink("data_sem");
	sem_close(data->data_sem);
	sem_unlink("forks_sem");
	sem_close(data->forks_sem);
	sem_unlink("print_sem");
	sem_close(data->print_sem);
	i = -1;
	while (++i < data->philos_nbr)
	{
		sem_unlink("philo_sem");
		sem_close(data->philos[i].philo_sem);
	}
}

void	ft_error(char *str)
{
	printf(RED"%s\n"RES, str);
	exit(1);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n > 0 && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
		n--;
	}
	return (0);
}
