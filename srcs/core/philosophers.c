/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:46:06 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/28 17:06:38 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

int 	philo_take_forks(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	if (philo->l_fork < philo->r_fork)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	pthread_mutex_lock(first_fork);
	print_status(philo, PHILO_TAKING_FORK);
	pthread_mutex_lock(second_fork);
	print_status(philo, PHILO_TAKING_FORK);
	return (1);
}

void	philo_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int 	philo_eat(t_philo *philo)
{
	print_status(philo, PHILO_EATING);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (1);
}

int 	philo_think(t_philo *philo)
{
	return (print_status(philo, PHILO_THINKING), 1);
}

int		philo_sleep(t_philo *philo)
{
	print_status(philo, PHILO_SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_running_state(philo->data))
	{
		if (philo->data->meals_count != -1
			&& philo->meals >= philo->data->meals_count)
			break ;
		philo_think(philo);
		philo_take_forks(philo);
		if (!philo_eat(philo))
			break ;
		philo_drop_forks(philo);
		if (!philo_sleep(philo))
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor_thread;

	if ((ac != 5 && ac != 6) || !is_numeric_args(av + 1))
		return (printf("%s\n", ERR_ARGS_TYPE), 1);
	data.is_running = true;
	init_data(&data, av);
	init_philosophers(&data);
	pthread_create(&monitor_thread, NULL, monitor_routine, &data);
	wait_philosophers(&data);
	pthread_join(monitor_thread, NULL);
	return (0);
}
