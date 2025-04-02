/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:46:06 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/02 09:50:05 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

int 	check_meals(t_philo *philo)
{
	if (philo->data->m_count > 0 && philo->meals_nb >= philo->data->m_count)
	{
		pthread_mutex_lock(&philo->data->write_mutex);
		philo->data->nb_of_meals++;
		pthread_mutex_unlock(&philo->data->write_mutex);
		return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	philo->meal_l = philo->data->start_t;
	if (philo->id % 2)
		usleep(500);
	while (!philo->data->stop)
	{
		if (!philo_think(philo))
			break ;
		if (!philo_take_forks(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		philo_release_forks(philo);
		if (!philo_sleep(philo))
			break ;
	}
	philo_release_forks(philo);
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
	pthread_t	monitor;

	if ((ac != 5 && ac != 6) || !is_numeric_args(av + 1))
		return (printf("%s\n", ERR_ARGS_TYPE), 0);
	if (!init_data(&dp, av))
		return (printf("%s\n", ERR_MAX_INT), 0);
	dp.dt.start_t = get_time_in_ms();
	if (!init_philosophers(&dp))
		return (printf("%s\n", ERROR_INIT_PHILOS), 0);
	if (!start_threads(&dp))
		return (printf("%s\n", ERR_START_THREAD), 0);
	pthread_create(&monitor, NULL, &global_monitor, &dp);
	wait_philosophers(&dp);
	pthread_join(monitor, NULL);
	free_philosophers(&dp);
	return (1);
}
