/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_kinds_of_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:42:21 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/24 12:16:58 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

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

void	wait_philosophers(t_dp *dp)
{
	int	i;

	i = 0;
	while (i < dp->dt.philo_count)
	{
		pthread_join(dp->ph[i].thread_id, NULL);
		i++;
	}
}

void	free_philosophers(t_dp *dp)
{
	int	i;

	if (!dp->ph)
		return ;
	i = 0;
	while (i < dp->dt.philo_count)
	{
		pthread_mutex_destroy(&dp->ph[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&dp->dt.write_mutex);
	free(dp->ph);
}