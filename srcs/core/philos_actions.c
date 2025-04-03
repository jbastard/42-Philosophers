/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:24:29 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/03 12:55:27 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	philo_think(t_philo	*philo)
{
	print_status(philo, PHILO_THINKING);
	return (1);
}

int	philo_take_forks(t_philo *philo)
{
	if (is_running(philo->data))
		return (0);
	if (philo->data->philo_count == 1 && !is_running(philo->data))
	{
		print_status(philo, PHILO_TAKING_FORK);
		ft_usleep(philo->data->die_t + 1, philo->data);
		return (0);
	}
	else if (!philo->id % 2)
	{
		pthread_mutex_lock(&philo->l_fork);
		print_status(philo, PHILO_TAKING_FORK);
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, PHILO_TAKING_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, PHILO_TAKING_FORK);
		pthread_mutex_lock(&philo->l_fork);
		print_status(philo, PHILO_TAKING_FORK);
	}
	return (1);
}

int	philo_eat(t_philo *philo)
{
	print_status(philo, PHILO_EATING);
	set_meal_nb(philo, get_meal_nb(philo) + 1);
	set_meal_l(philo, get_time_in_ms());
	ft_usleep(philo->data->eat_t, philo->data);
	if (philo->data->m_count > 0 && get_meal_nb(philo) == philo->data->m_count)
		set_nb_of_meals(philo->data, get_nb_of_meals(philo->data) + 1);
	return (1);
}

int	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	return (1);
}

int	philo_sleep(t_philo	*philo)
{
	print_status(philo, PHILO_SLEEPING);
	ft_usleep(philo->data->sleep_t, philo->data);
	return (1);
}
