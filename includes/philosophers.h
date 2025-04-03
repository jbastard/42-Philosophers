/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/03 10:35:01 by jbastard         ###   ########.fr       */
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
# include <limits.h>

	//ERROR
# define ERR_START_THREAD "Unable to create threads for philos"
# define ERR_ARGS_TYPE "Error: Invalid arguments\n\
Usage: ./philosophers number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"
# define ERROR_INIT_PHILOS "Unable to load philos"
# define ERR_MAX_INT "Values needs to be between INT_MAX & 1"

	//PHILO ACTIONS
# define PHILO_TAKING_FORK "as taken a fork"
# define PHILO_EATING "is eating"
# define PHILO_THINKING "is thinking"
# define PHILO_SLEEPING "is sleeping"
# define PHILO_DIE "died"
# define PHILO_FULL "Philosophers have completed their meals"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_dp		t_dp;

struct s_data
{
	int				philo_count;
	long int		sleep_t;
	long int		die_t;
	long int		eat_t;
	int				m_count;
	long int		start_t;
	pthread_mutex_t running_mutex;
	pthread_mutex_t	meal_l_mutex;
	pthread_mutex_t	write_mutex;
	int				nb_of_meals;
	int				stop;
};

struct s_philo
{
	int				id;
	pthread_t		thread_id;
	long			start_time;
	int				meals_nb;
	long int		meal_l;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
};

struct s_dp
{
	t_philo			*ph;
	t_data			dt;
};

int			is_running(t_data *data);
void		set_running(t_data *data, int status);
long int	get_meal_l(t_philo *philo);
void		set_meal_l(t_philo *philo, long int value);
void		set_meal_nb(t_philo *philo, int value);
int			get_meal_nb(t_philo *philo);
int			get_nb_of_meals(t_data *data);
void		set_nb_of_meals(t_data *data, int value);

//CORE
	//PHILOSOPHERS.C
void		*routine(void *arg);
	//INIT.C
int			init_data(t_dp *data, char **av);
int			init_philosophers(t_dp *data);
	//MONITOR.C
void		*global_monitor(void *arg);
	// PHILOS ACTIONS.C
int			philo_think(t_philo	*philo);
int			philo_take_forks(t_philo *philo);
int			philo_eat(t_philo *philo);
int			philo_release_forks(t_philo *philo);
int			philo_sleep(t_philo	*philo);

//UTILS
	//LIBFT_UTILS.C
int			is_digit(int c);
int			ft_atoi(const char *str);
long long	ft_atol(const char *str);
int			is_numeric_args(char **av);
int			ft_strncmp(const char	*s1, const char	*s2, size_t	n);
	//UTILS.C
long int	get_time_in_ms(void);
void		print_status(t_philo *philo, char *status);
void		ft_usleep(long int time_in_ms, t_data *data);
	//MONITOR_MANAGER.C
void		free_philosophers(t_dp *dp);
void		wait_philosophers(t_dp *dp);
int			start_threads(t_dp	*dp);

#endif
