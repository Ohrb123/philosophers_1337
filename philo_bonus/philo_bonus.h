/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrb <hrb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:14:10 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/26 13:34:09 by hrb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

//INCLUDES

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <stdatomic.h>

//COLORES

# define RED			"\x1b[1;31m"
# define RES			"\x1b[0m"

//TYPEDEFS

typedef struct s_data			t_data;
typedef struct s_philo			t_philo;

//STRUCTURES

struct s_philo
{
	int					id;
	pid_t				pid;
	t_data				*data;
	_Atomic size_t		last_meal;
	int					meals_nbr;
	sem_t				*philo_sem;
};

struct s_data
{
	int					philos_nbr;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					times_must_eat;
	sem_t				*print_sem;
	sem_t				*data_sem;
	size_t				start;
	t_philo				*philos;
	sem_t				*forks_sem;
	int					dead;
};

//PHILOSOPHERS_FUNCTIONS

void	create_philos(t_data *data, char **av);
int		ft_atol(char *str);
size_t	get_time(void);
int		check_all_threads(t_data *data);
void	ft_error(char *str);
void	my_usleep(size_t time);
void	*dead_check(void *content);
int		is_die(t_data *data);
void	my_printf(t_philo *philo, char *str);
void	start_simulation(t_data *data);
int		is_dead(t_data *data);
void	ft_parsing(t_data *data, char **av);
void	ft_close(t_data *data);

#endif