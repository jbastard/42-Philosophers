///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   init.c                                             :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2025/03/24 11:50:39 by jbastard          #+#    #+#             */
///*   Updated: 2025/03/25 11:50:48 by jbastard         ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "../../includes/philosophers.h"
//
//void init_philo_forks(t_data *data)
//{
//	int i;
//
//	i = 0;
//	while (i < data->philo_count)
//	{
//		data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_count];
//		i++;
//	}
//}
//
//void	init_forks(t_data *data)
//{
//	int i;
//
//	i = 0;
//	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
//	while (i < data->philo_count)
//		pthread_mutex_init(&data->forks[i++], NULL);
//}
//
//int init_philosophers(t_data *data)
//{
//	int i;
//
//	i = 0;
//	data->philos = malloc(sizeof(t_philo) * data->philo_count);
//	if (!data->philos)
//		return (printf("%s\n", ERR_MALLOC), 0);
//	while (i < data->philo_count)
//	{
//		data->philos[i].id = i;
//		data->philos[i].meals = 0;
//		data->philos[i].last_meal = get_time_in_ms();
//		data->philos[i].data = data;
//		data->philos[i].l_fork = &data->forks[i];
//		if (pthread_create(&data->philos[i].thread_id,
//						   NULL, routine, &data->philos[i]))
//			return (perror("pthread_create"), 0);
//		usleep(100);
//		i++;
//	}
//	init_philo_forks(data);
//	pthread_mutex_lock(&data->is_running_mutex);
//	data->start_time = get_time_in_ms();
//	data->is_running = true;
//	pthread_mutex_unlock(&data->is_running_mutex);
//	return (1);
//}
//
//int init_data(t_data *data, char **av)
//{
//	if (!is_numeric_args(av + 1))
//		return (printf("%s\n", ERR_ARGS_TYPE), 0);
//	data->philo_count = ft_atoi(av[1]);
//	data->time_to_die = ft_atoi(av[2]);
//	data->time_to_eat = ft_atoi(av[3]);
//	data->time_to_sleep = ft_atoi(av[4]);
//	data->is_running = false;
//	init_forks(data);
//	if (av[5])
//		data->meals_count = ft_atoi(av[5]);
//	else
//		data->meals_count = -1;
//	return (1);
//}
