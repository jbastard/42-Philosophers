/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:52:15 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/03 12:54:26 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int 	is_running(t_data *data)
{
	int ret;

	pthread_mutex_lock(&data->running_mutex);
	ret = data->stop;
	pthread_mutex_unlock(&data->running_mutex);
	return (ret);
}

void 	set_running(t_data *data, int status)
{
	pthread_mutex_lock(&data->running_mutex);
	data->stop = status;
	pthread_mutex_unlock(&data->running_mutex);
}

void set_meal_l(t_philo *philo, long int value)
{
	pthread_mutex_lock(&philo->data->meal_l_mutex);
	philo->meal_l = value;
	pthread_mutex_unlock(&philo->data->meal_l_mutex);
}

long int	get_meal_l(t_philo *philo)
{
	long int	ret;

	pthread_mutex_lock(&philo->data->meal_l_mutex);
	ret = philo->meal_l;
	pthread_mutex_unlock(&philo->data->meal_l_mutex);
	return (ret);
}

void set_meal_nb(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->data->meal_l_mutex);
	philo->meals_nb = value;
	pthread_mutex_unlock(&philo->data->meal_l_mutex);
}

int	get_meal_nb(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->meal_l_mutex);
	ret = philo->meals_nb;
	pthread_mutex_unlock(&philo->data->meal_l_mutex);
	return (ret);
}

void set_nb_of_meals(t_data *data, int value)
{
	pthread_mutex_lock(&data->meal_l_mutex);
	data->nb_of_meals = value;
	pthread_mutex_unlock(&data->meal_l_mutex);
}

int	get_nb_of_meals(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->meal_l_mutex);
	ret = data->nb_of_meals;
	pthread_mutex_unlock(&data->meal_l_mutex);
	return (ret);
}

int	philo_did_die(t_dp *dp)
{
	int		i;
	long	time;

	i = 0;
	while (i < dp->dt.philo_count)
	{
		time = get_time_in_ms() - get_meal_l(&dp->ph[i]);
		if ((dp->dt.m_count < 0 || get_meal_nb(&dp->ph[i]) < dp->dt.m_count)
			&& time > dp->dt.die_t)
		{
			print_status(&dp->ph[i], PHILO_DIE);
			set_running(&dp->dt, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*global_monitor(void *arg)
{
	t_dp	*dp;
	int		i;

	dp = (t_dp *)arg;
	while (!is_running(&dp->dt))
	{
		if (philo_did_die(dp))
			return (NULL);
		i = 0;
		if (dp->dt.m_count > 0 && get_nb_of_meals(&dp->dt) >= dp->dt.philo_count)
		{
			set_running(&dp->dt, 1);
			pthread_mutex_lock(&dp->dt.write_mutex);
			printf("%s\n", PHILO_FULL);
			pthread_mutex_unlock(&dp->dt.write_mutex);
			break ;
		}
		usleep(50);
	}
	return (NULL);
}
