/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:26:57 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/16 10:26:20 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	check_sign(char *str)
{
	if (!ft_isdigit(*(str + 1)))
		return (0);
	if (*str == '-')
		return (0);
	return (1);
}

int	ft_atol(char *str)
{
	int	result;
	int	check;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (!check_sign(str))
			return (0);
		str++;
	}
	while (*str)
	{
		check = result;
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		result = result * 10 + (*str - 48);
		if (result / 10 != check)
			return (0);
		str++;
	}
	if (result > INT_MAX)
		return (0);
	return (result);
}

int	ft_parsing(t_data *data, char **av)
{
	data->philos_nbr = ft_atol(av[1]);
	if (data->philos_nbr > 200 || data->philos_nbr <= 0)
		return (ft_error("ERROR : Please enter a valid number \
of philos in this range ]0 to 200]"));
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (ft_error("ERROR : Please enter a valid time and \
greater than ZERO and less than INT_MAX!!"));
	if (av[5])
	{
		data->times_must_eat = ft_atol(av[5]);
		if (data->times_must_eat <= 0)
			return (ft_error("ERROR : Please enter a valid number of \
meals greater than ZERO and less than INT_MAX!!"));
	}
	else
		data->times_must_eat = -1337;
	return (0);
}
