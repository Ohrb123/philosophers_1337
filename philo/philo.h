/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:14:10 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/20 15:14:24 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//INCLUDES

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>

//COLORES

# define RED			"\x1b[1;31m"
# define RES			"\x1b[0m"

//TYPEDEFS

typedef struct s_data			t_data;
typedef struct s_philo			t_philo;

//STRUCTURES

struct s_philo
{
	t_data				*data;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	int					id;
	size_t				last_meal;
	pthread_mutex_t		philo_lock;
	pthread_t			thread;
	int					meals_nbr;
};

struct s_data
{
	int					philos_nbr;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					times_must_eat;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		data_lock;
	size_t				start;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					dead;
};

//PHILOSOPHERS_FUNCTIONS

int		create_philos(t_data *data, char **av);
int		ft_atol(char *str);
size_t	get_time(void);
int		ft_error(char *str);
void	my_usleep(size_t time, t_data *data);
void	*dead_check(void *content);
int		is_die(t_data *data);
void	start_simulation(t_data *data);
int		ft_parsing(t_data *data, char **av);

#endif