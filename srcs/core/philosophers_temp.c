/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_temp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 07:46:41 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/25 12:47:59 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   philosophers.c                                     :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
///*   Updated: 2025/03/25 12:42:18 by jbastard         ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "../../includes/philosophers.h"
//
//void	philo_is_dead(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->data->is_running_mutex);
//	if (!philo->data->is_running)
//		printf("%d: %d died\n", philo->data->time_to_die, philo->id + 1);
//	pthread_mutex_unlock(&philo->data->is_running_mutex);
//}
//
//int elapsed_time(t_data *data)
//{
//	int elapsed_time;
//
//	pthread_mutex_lock(&data->start_time_mutex);
//	elapsed_time = get_time_in_ms() - data->start_time;
//	pthread_mutex_unlock(&data->start_time_mutex);
//	return (elapsed_time);
//}
//
//bool check_is_running(t_data *data)
//{
//	bool result;
//	pthread_mutex_lock(&data->is_running_mutex);
//	result = data->is_running;
//	pthread_mutex_unlock(&data->is_running_mutex);
//	return (result);
//}
//
//int has_philo_die(t_philo	*philo)
//{
//	pthread_mutex_lock(&philo->data->is_running_mutex);
//	if (philo->data->is_running
//		&& (get_time_in_ms() - philo->last_meal) > philo->data->time_to_die)
//	{
//		philo->data->is_running = false;
//		pthread_mutex_unlock(&philo->data->is_running_mutex);
//		return (1);
//	}
//	pthread_mutex_unlock(&philo->data->is_running_mutex);
//	return (0);
//}
//
//void smart_sleep(t_data *data, long long time_to_wait)
//{
//	long long start_time;
//
//	start_time = get_time_in_ms();
//	while (check_is_running(data) && (get_time_in_ms() - start_time) < time_to_wait)
//		usleep(500);
//}
//
//void start_eating(t_philo *philo)
//{
//	if (has_philo_die(philo))
//	{
//		philo_is_dead(philo);
//		return ;
//	}
//	pthread_mutex_lock(philo->l_fork);
//	printf("%d: %d as taken a fork\n", elapsed_time(philo->data), philo->id + 1);
//	pthread_mutex_lock(philo->r_fork);
//	printf("%d: %d as taken a fork\n", elapsed_time(philo->data), philo->id + 1);
//	if (!check_is_running(philo->data))
//	{
//		pthread_mutex_unlock(philo->l_fork);
//		pthread_mutex_unlock(philo->r_fork);
//		return ;
//	}
//	printf("%d: %d is eating\n", elapsed_time(philo->data), philo->id + 1);
//	smart_sleep(philo->data, philo->data->time_to_eat);
//	pthread_mutex_unlock(philo->l_fork);
//	pthread_mutex_unlock(philo->r_fork);
//}
//
//void	start_sleeping(t_philo *philo)
//{
//	printf("%d: %d is sleeping\n", elapsed_time(philo->data), philo->id + 1);
//	smart_sleep(philo->data, philo->data->time_to_sleep);
//}
//
//void *routine(void *r_philo)
//{
//	t_philo *philo;
//
//	philo = (t_philo *)r_philo;
//	while (!check_is_running(philo->data))
//		usleep(100);
//	while (check_is_running(philo->data))
//	{
//		printf("%d: %d is thinking\n", elapsed_time(philo->data), philo->id + 1);
//		if (check_is_running(philo->data))
//			start_eating(philo);
//		philo->last_meal = get_time_in_ms();
//		if (has_philo_die(philo))
//			philo_is_dead(philo);
//		if (check_is_running(philo->data))
//			start_sleeping(philo);
//		if (has_philo_die(philo))
//			return (philo_is_dead(philo), NULL);
//	}
//	return (NULL);
//}
//
//void	wait_philosophers(t_data *data)
//{
//	int i;
//
//	i = 0;
//	while (i < data->philo_count)
//		pthread_join(data->philos[i++].thread_id, NULL);
//}
//
//int main(int ac, char **av)
//{
//	t_data data;
//
//	if (ac != 5 && ac != 6)
//		return (printf("%s\n", ERR_ARGS_COUNT));
//	pthread_mutex_init(&data.is_running_mutex, NULL);
//	pthread_mutex_init(&data.start_time_mutex, NULL);
//	if (!init_data(&data, av))
//		return (0);
//	if (!init_philosophers(&data))
//		return (0);
//	wait_philosophers(&data);
//	pthread_mutex_destroy(&data.is_running_mutex);
//	pthread_mutex_destroy(&data.start_time_mutex);
//	return (1);
//}
