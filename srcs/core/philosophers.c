/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:46:06 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/01 09:10:06 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

int 	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (philo->data->m_count != -1 && philo->meals_nb >= philo->data->m_count)
		return (pthread_mutex_unlock(&philo->data->write_mutex), 0);
	return (pthread_mutex_unlock(&philo->data->write_mutex), 1);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philo;
	long int	time;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->write_mutex);
		time = get_time_in_ms() - philo->meal_l;
		if (time > philo->data->die_t)
		{
			if (!philo->data->stop && !check_meals(philo))
			{
				print_status(philo, PHILO_DIE);
				philo->data->stop = 1;
			}
			pthread_mutex_unlock(&philo->data->write_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->write_mutex);
		usleep(500);
	}
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	philo->meal_l = get_time_in_ms();
	pthread_create(&philo->thread_mo_id, NULL, monitor_routine, philo);
	if (philo->id % 2)
		usleep(500);
	while (1)
	{
		if (!check_meals(philo))
			break ;
		if (!philo_think(philo) || philo->data->stop || !check_meals(philo))
			break ;
		if (!philo_take_forks(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		philo_release_forks(philo);
		if (!philo_sleep(philo) || philo->data->stop || !check_meals(philo))
			break ;
	}
	philo_release_forks(philo);
	pthread_join(philo->thread_mo_id, NULL);
	return (NULL);
}

int 	start_threads(t_dp	*dp)
{
	int	i;

	i = 0;
	while (i < dp->dt.philo_count)
	{
		if (pthread_create(&dp->ph[i].thread_id, NULL, &routine, &dp->ph[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_dp	dp;

	if ((ac != 5 && ac != 6) || !is_numeric_args(av + 1))
		return (printf("%s\n", ERR_ARGS_TYPE), 0);
	if (!init_data(&dp, av))
		return (printf("%s\n", ERROR_INIT_DATA), 0);
	if (!init_philosophers(&dp))
		return (printf("%s\n", ERROR_INIT_PHILOS), 0);
	if (!start_threads(&dp))
		return (printf("%s\n", ERR_START_THREAD), 0);
	wait_philosophers(&dp);
	return (1);
}
