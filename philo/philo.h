/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:14:10 by oelharbi          #+#    #+#             */
/*   Updated: 2024/08/17 21:57:46 by oelharbi         ###   ########.fr       */
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
	int					times_must_eat;
	size_t				last_meal;
	pthread_mutex_t		philo_lock;
	pthread_t			thread;
	int					dead;
};

struct s_data
{
	pthread_mutex_t		dead_lock;
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
};

//PHILOSOPHERS_FUNCTIONS

int		create_philos(t_data *data, char **av);
int		ft_atol(char *str);
size_t	get_time(void);
int		ft_error(char *str);
void	my_usleep(size_t time);
void	*dead_check(void *content);
int	is_dead(t_data *data);
void	start_simulation(t_data *data);
int		ft_parsing(t_data *data, char **av);
// void	my_printf(t_data *data, char *str, int id);

#endif