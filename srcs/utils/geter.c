/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:10:43 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/07 12:10:43 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	is_running(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->running_mutex);
	ret = data->stop;
	pthread_mutex_unlock(&data->running_mutex);
	return (ret);
}

int	get_nb_of_meals(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->meal_l_mutex);
	ret = data->nb_of_meals;
	pthread_mutex_unlock(&data->meal_l_mutex);
	return (ret);
}

int	get_meal_nb(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data->meal_l_mutex);
	ret = philo->meals_nb;
	pthread_mutex_unlock(&philo->data->meal_l_mutex);
	return (ret);
}

long int	get_meal_l(t_philo *philo)
{
	long int	ret;

	pthread_mutex_lock(&philo->data->meal_l_mutex);
	ret = philo->meal_l;
	pthread_mutex_unlock(&philo->data->meal_l_mutex);
	return (ret);
}
