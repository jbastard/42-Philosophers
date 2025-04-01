/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:45:50 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/31 12:00:50 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

int	init_data(t_dp *dp, char **av)
{
	t_data	data;

	data.philo_count = ft_atoi(av[1]);
	data.die_t = ft_atol(av[2]);
	data.eat_t = ft_atol(av[3]);
	data.sleep_t = ft_atol(av[4]);
	if (av[5])
		data.m_count = ft_atoi(av[5]);
	else
		data.m_count = -1;
	data.start_t = get_time_in_ms();
	data.stop = 0;
	pthread_mutex_init(&data.write_mutex, NULL);
	dp->dt = data;
	return (1);
}

int	init_philosophers(t_dp *dp)
{
	int i;

	i = 0;
	dp->ph= malloc(sizeof(t_philo) * dp->dt.philo_count);
	while (i < dp->dt.philo_count)
	{
		dp->ph[i].id = i;
		dp->ph[i].meals_nb = 0;
		dp->ph[i].meal_l = 0;
		dp->ph[i].data = &dp->dt;
		dp->ph[i].finish = 0;
		pthread_mutex_init(&dp->ph[i].l_fork, NULL);
		i++;
	}
	i = 0;
	while (i < dp->dt.philo_count)
	{
		dp->ph[i].r_fork = &dp->ph[(i + 1) % dp->dt.philo_count].l_fork;
		i++;
	}
	return (1);
}
