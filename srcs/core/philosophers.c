/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:46:06 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/28 12:59:48 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->start_time_mutex);
	printf("%-7lld %d %s\n",
			get_time_in_ms() - philo->data->start_time, philo->id + 1, status);
	pthread_mutex_unlock(&philo->data->start_time_mutex);
}

int 	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, PHILO_TAKING_FORK);
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, PHILO_TAKING_FORK);
	philo->meals++;
	print_status(philo, PHILO_EATING);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->last_meal = get_time_in_ms();
	return (1);
}

int 	philo_sleep(t_philo *philo)
{
	if (philo->data->time_to_die > philo->data->time_to_sleep)
	{
		usleep(philo->data->time_to_die);
		pthread_mutex_lock(&philo->data->is_running_mutex);
		philo->data->is_running = false;
		pthread_mutex_unlock(&philo->data->is_running_mutex);
		print_status(philo, PHILO_DIE);
		return (0);
	}
	else
	{
		print_status(philo, PHILO_SLEEPING);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (1);
}

int 	philo_think(t_philo *philo)
{
	print_status(philo, PHILO_THINKING);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->is_running)
		usleep(20);
	while (philo->data->is_running)
	{
		if (philo->data->meals_count != -1
			&& philo->meals >= philo->data->meals_count)
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	pthread_mutex_lock(&philo->data->is_running_mutex);
	philo->data->is_running = false;
	pthread_mutex_unlock(&philo->data->is_running_mutex);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac != 5 && ac != 6) || !is_numeric_args(av + 1))
		return (printf("%s\n", ERR_ARGS_TYPE), 1);
	init_data(&data, av);
	init_philosophers(&data);
	wait_philosophers(&data);
	return (0);
}
