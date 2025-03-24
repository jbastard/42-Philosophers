/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/24 13:06:53 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int is_dead(t_philo	*philo)
{
	if (get_time_in_ms() - philo->last_meal > philo->data->time_to_die)
		return (printf("%d died\n", philo->id), 1);
	return (0);
}

void *routine(void *r_philo)
{
	t_philo *philo = (t_philo *)r_philo;

	printf("%d\n", philo->id);
	while (1)
	{
		philo->last_meal = get_time_in_ms();
		if (is_dead(philo))
			break ;
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac != 6)
		return (printf("%s\n", ERR_ARGS_COUNT));
	if (!init_data(&data, av))
		return (0);
	if (!init_philosophers(&data))
		return (perror("Error"), 0);
	free_philos(&data);
	return (1);
}
