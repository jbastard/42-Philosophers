/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/23 17:35:43 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *routine(void *r_data)
{
	t_data *data = (t_data *)r_data;
	pthread_mutex_lock(&data->mutester);
	for (int i = 0; i < 20000; ++i) {
		data->meals_count++;
	}
	pthread_mutex_unlock(&data->mutester);
	return NULL;
}

int init_philosophers(t_data *data)
{
	int i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (printf("%s\n", ERR_MALLOC), 0);
	pthread_mutex_init(&data->mutester, NULL);
	while (i < data->philo_count)
	{
		printf("i: %d\n", i);
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = 0;
		if (pthread_create(&data->philos[i].thread, NULL,
							routine, &data))
			return (perror("pthread_create"), 0);
		i++;
	}
	return (1);
}

int init_data(t_data *data, char **av)
{
	if (!is_numeric_args(av + 1))
		return (printf("%s\n", ERR_ARGS_TYPE), 0);
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals_count = ft_atoi(av[5]);
	else
		data->meals_count = -1;
	return (1);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac != 6)
		return (printf("%s\n", ERR_ARGS_COUNT));
	if (!init_data(&data, av))
		return (0);
	if (!init_philosophers(&data))
		return (perror("Error"), free_philos(&data), 0);
	free_philos(&data);
	printf("%d\n", data.meals_count);
	pthread_mutex_destroy(&data.mutester);
	return (1);
}
