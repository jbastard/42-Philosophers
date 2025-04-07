/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:09:47 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/07 12:09:47 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	set_running(t_data *data, int status)
{
	pthread_mutex_lock(&data->running_mutex);
	data->stop = status;
	pthread_mutex_unlock(&data->running_mutex);
}

void	set_meal_l(t_philo *philo, long int value)
{
	pthread_mutex_lock(&philo->data->meal_l_mutex);
	philo->meal_l = value;
	pthread_mutex_unlock(&philo->data->meal_l_mutex);
}

void	set_meal_nb(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->data->meal_l_mutex);
	philo->meals_nb = value;
	pthread_mutex_unlock(&philo->data->meal_l_mutex);
}

void	set_nb_of_meals(t_data *data, int value)
{
	pthread_mutex_lock(&data->meal_l_mutex);
	data->nb_of_meals = value;
	pthread_mutex_unlock(&data->meal_l_mutex);
}
