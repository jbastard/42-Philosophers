/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/23 15:47:31 by jbastard         ###   ########.fr       */
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

# define ERR_MALLOC "Error: Memory allocation failed"
# define ERR_ARGS_COUNT "Error: Wrong number of arguments"
# define ERR_ARGS_TYPE "Error: Invalid arguments\n\
Usage: ./philosophers number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"

typedef struct s_data t_data;
typedef struct s_philo t_philo;

struct s_data {
	int				philo_count;
	int				meals_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			*philos;
};

struct s_philo {
	int				id;
	int				meals;
	int				last_meal;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
};

int is_digit(int c);
int ft_atoi(char *str);
int is_numeric_args(char **av);

#endif
