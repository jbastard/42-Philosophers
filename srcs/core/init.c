/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:45:50 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/28 16:37:05 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

void init_data(t_data *data, char **av)
{
	data->philo_count = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (av[5])
		data->meals_count = atoi(av[5]);
	else
		data->meals_count = -1;
	pthread_mutex_init(&data->is_running_mutex, NULL);
	pthread_mutex_init(&data->start_time_mutex, NULL);
	pthread_mutex_init(&data->meals_mutex, NULL);
	data->start_time = get_time_in_ms();
	if (data->philo_count == 1)
		data->forks = malloc(sizeof(pthread_mutex_t));
	else
		data->forks = malloc(sizeof(pthread_mutex_t) * (data->philo_count + 1));
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
}

void	init_forks(t_data *data, int i)
{
	if (data->philo_count == 1)
	{
		data->philos[i].l_fork = &data->forks[0];
		data->philos[i].r_fork = &data->forks[0];
	}
	else
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_count];
	}
}

void init_philosophers(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = get_time_in_ms();
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].last_meal_mutex, NULL);
		init_forks(data, i);
		if (pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]))
			perror("pthread_create");
		usleep(20);
		i++;
	}
	data->start_time = get_time_in_ms();
}
