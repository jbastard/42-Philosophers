/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:52:15 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/02 12:27:08 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	philo_did_die(t_dp *dp)
{
	int		i;
	long	time;

	i = 0;
	while (i < dp->dt.philo_count)
	{
		time = get_time_in_ms() - dp->ph[i].meal_l;
		if ((dp->dt.m_count < 0 || dp->ph[i].meals_nb < dp->dt.m_count)
			&& time > dp->dt.die_t)
		{
			print_status(&dp->ph[i], PHILO_DIE);
			dp->dt.stop = 1;
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
	while (!dp->dt.stop)
	{
		if (philo_did_die(dp))
			return (NULL);
		i = 0;
		if (dp->dt.m_count > 0 && dp->dt.nb_of_meals >= dp->dt.philo_count)
		{
			dp->dt.stop = 1;
			return (printf("%s\n", PHILO_FULL), NULL);
		}
		usleep(100);
	}
	return (NULL);
}
