/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/24 13:24:41 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define ERR_MALLOC "Error: Memory allocation failed"
# define ERR_ARGS_COUNT "Error: Wrong number of arguments"
# define ERR_ARGS_TYPE "Error: Invalid arguments\n\
Usage: ./philosophers number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"

typedef struct s_data t_data;
typedef struct s_philo t_philo;

struct s_data {
	bool			is_running;
	pthread_mutex_t *is_running_mutex;
	int				philo_count;
	int				meals_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t *forks;
	t_philo			*philos;
};

struct s_philo {
	int				id;
	pthread_t		thread_id;
	int				meals;
	long long		last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
};

//CORE
int		init_data(t_data *data, char **av);
int		init_philosophers(t_data *data);
void	init_forks(t_data *data);
void	init_philo_forks(t_data *data);

void *routine(void *r_philo);

//UTILS
int			is_digit(int c);
int 		ft_atoi(char *str);
int			is_numeric_args(char **av);
long long	get_time_in_ms(void);

//ALL_KINDS_OF_FREE

#endif
