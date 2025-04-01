/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/31 11:42:32 by jbastard         ###   ########.fr       */
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

	//ERROR
# define ERR_ARGS_COUNT "Error: Wrong number of arguments"
# define ERR_MALLOC "Error: Memory allocation failed"
# define ERR_START_THREAD "Unable to create threads for philos"
# define ERR_ARGS_TYPE "Error: Invalid arguments\n\
Usage: ./philosophers number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"
# define ERROR_INIT_PHILOS "Unable to load philos"
# define ERROR_INIT_DATA "Unable to load data"
	//PHILO ACTIONS
# define PHILO_TAKING_FORK "\e[1;32mas taken a fork\033[0m"
# define PHILO_EATING "\e[1;92mis eating\033[0m"
# define PHILO_THINKING "\e[1;97mis thinking\033[0m"
# define PHILO_SLEEPING "\e[1;94mis sleeping\033[0m"
# define PHILO_DIE "\e[1;91mdied\033[0m"
# define PHILO_FULL "\e[1;93mAll philosophers have completed their meals.\033[0m"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_dp		t_dp;

struct s_data {
	int				philo_count;
	int				sleep_t;
	int				die_t;
	int				eat_t;
	int				m_count;
	long int 		start_t;
	pthread_mutex_t	write_mutex;
	int 			nb_of_meals;
	int				stop;
};

struct s_philo {
	int				id;
	pthread_t		thread_id;
	pthread_t		thread_mo_id;
	int				meals_nb;
	long int		meal_l;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
	int 			finish;
};

struct s_dp {
	t_philo			*ph;
	t_data			dt;
};

//CORE
	//PHILOSOPHERS.C
void		*routine(void *arg);
	//INIT.C
int			init_data(t_dp *data, char **av);
int			init_philosophers(t_dp *data);
	//MONITOR.C
void		*monitor_routine(void *arg);
// PHILOS ACTIONS.C
int			philo_think(t_philo	*philo);
int 		philo_take_forks(t_philo *philo);
int			philo_eat(t_philo *philo);
int 		philo_release_forks(t_philo *philo);
int 		philo_sleep(t_philo	*philo);

int 	check_meals(t_philo *philo);

//UTILS
	//LIBFT_UTILS.C
int			is_digit(int c);
int 		ft_atoi(const char *str);
long int 		ft_atol(const char *str);
int			is_numeric_args(char **av);
	//UTILS.C
long int	elapsed_time(t_data *data);
long int	get_time_in_ms(void);
void		wait_philosophers(t_dp *dp);
void		print_status(t_philo *philo, char *status);
void		ft_usleep(long int time_in_ms, t_data *data);

//ALL_KINDS_OF_FREE

#endif
