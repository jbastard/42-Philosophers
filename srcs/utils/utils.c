/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:58:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/25 14:32:29 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

int elapsed_time(t_data *data)
{
	int elapsed_time;

	pthread_mutex_lock(&data->start_time_mutex);
	elapsed_time = get_time_in_ms() - data->start_time;
	pthread_mutex_unlock(&data->start_time_mutex);
	return (elapsed_time);
}

void wait_philosophers(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
		pthread_join(data->philos[i++].thread_id, NULL);
}

long long get_time_in_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int 	check_running_state(t_data *data)
{
	bool state;

	pthread_mutex_lock(&data->is_running_mutex);
	state = data->is_running;
	pthread_mutex_unlock(&data->is_running_mutex);
	return (state);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->is_running_mutex);
	if (philo->data->is_running == true)
		printf("%-7lld %d : %s\n",
			   get_time_in_ms() - philo->data->start_time,
			   philo->id + 1, status);
	pthread_mutex_unlock(&philo->data->is_running_mutex);
}
