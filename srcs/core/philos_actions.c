/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:24:29 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/01 11:39:42 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int		philo_think(t_philo	*philo)
{
	print_status(philo, PHILO_THINKING);
	return (1);
}

int philo_take_forks(t_philo *philo)
{
	if (philo->data->stop)
		return (0);
	if (philo->data->philo_count == 1)
		return (print_status(philo, PHILO_TAKING_FORK), 0);
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

int		philo_eat(t_philo *philo)
{
	print_status(philo, PHILO_EATING);
	philo->meals_nb++;
//	printf("%d philo :%d\n", philo->id + 1, philo->meals_nb);
	philo->meal_l = get_time_in_ms();
	ft_usleep(philo->data->eat_t, philo->data);
	if (!check_meals(philo))
		return (0);
	return (1);
}

int 	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	return (1);
}

int 	philo_sleep(t_philo	*philo)
{
	print_status(philo, PHILO_SLEEPING);
	ft_usleep(philo->data->sleep_t, philo->data);
	return (1);
}