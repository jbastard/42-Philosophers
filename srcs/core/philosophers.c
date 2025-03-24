/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/24 13:52:02 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int is_dead(t_philo	*philo)
{
	if (get_time_in_ms() - philo->last_meal > (long long)philo->data->time_to_die)
		return (printf("%d died\n", philo->id), 1);
	return (0);
}

void *routine(void *r_philo)
{
	t_philo *philo = (t_philo *)r_philo;

	while (philo->data->is_running)
	{
		philo->last_meal = get_time_in_ms();
		usleep(philo->data->time_to_eat * 1000);
		if (is_dead(philo))
			break ;
	}
	philo->data->is_running = false;
	return (NULL);
}

void	wait_philosophers(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
		pthread_join(data->philos[i++].thread_id, NULL);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac != 6)
		return (printf("%s\n", ERR_ARGS_COUNT));
	if (!init_data(&data, av))
		return (0);
	if (!init_philosophers(&data))
		return (0);
	wait_philosophers(&data);
	return (1);
}
