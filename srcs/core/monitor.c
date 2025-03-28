/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:52:15 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/28 16:06:31 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->is_running_mutex);
	data->is_running = false;
	pthread_mutex_unlock(&data->is_running_mutex);
}

bool	philo_died(t_philo *philo)
{
	long long	current_time;
	bool		is_dead;

	pthread_mutex_lock(&philo->last_meal_mutex);
	current_time = get_time_in_ms();
	is_dead = (current_time - philo->last_meal >= philo->data->time_to_die);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (is_dead);
}

bool	all_philos_full(t_data *data)
{
	int		i;
	bool	full;

	if (data->meals_count == -1)
		return (false);
	i = 0;
	full = true;
	pthread_mutex_lock(&data->meals_mutex);
	while (i < data->philo_count)
	{
		if (data->philos[i].meals < data->meals_count)
			full = false;
		i++;
	}
	pthread_mutex_unlock(&data->meals_mutex);
	return (full);
}

void	*monitor_routine(void *arg)
{
	int i;
	t_data *data;

	data = (t_data *)arg;
	while (check_running_state(data))
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (philo_died(&data->philos[i]))
			{
				print_status(&data->philos[i], PHILO_DIE);
				stop_simulation(data);
				return (NULL);
			}
			i++;
		}
		if (all_philos_full(data))
		{
			stop_simulation(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
