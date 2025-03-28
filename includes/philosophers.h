/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/28 12:04:43 by jbastard         ###   ########.fr       */
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
# define PHILO_TAKING_FORK "\e[1;32m : taking a fork\033[0m"
# define PHILO_EATING "\e[1;92m : is eating\033[0m"
# define PHILO_THINKING "\e[1;97m : is thinking\033[0m"
# define PHILO_SLEEPING "\e[1;94m : is sleeping\033[0m"
# define PHILO_DIE "\e[1;91m : is dead\033[0m"

typedef struct s_data t_data;
typedef struct s_philo t_philo;

struct s_data {
	int				philo_count;
	int				time_to_sleep;
	int				time_to_die;
	int				time_to_eat;
	int				meals_count;
	bool			is_running;
	pthread_mutex_t is_running_mutex;
	long long		start_time;
	pthread_mutex_t start_time_mutex;
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
void		init_data(t_data *data, char **av);
void		init_philosophers(t_data *data);
void		init_forks(t_data *data, int i);

void		*routine(void *r_philo);

//UTILS
int			is_digit(int c);
int 		ft_atoi(char *str);
int			is_numeric_args(char **av);
int			elapsed_time(t_data *data);

long long	get_time_in_ms(void);
void		wait_philosophers(t_data *data);

//ALL_KINDS_OF_FREE

#endif
