/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:58:00 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/02 09:46:10 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

void	ft_usleep(long int time, t_data *data)
{
	long int	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time)
	{
		pthread_mutex_lock(&data->write_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->write_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->write_mutex);
		usleep(500);
	}
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

long int get_time_in_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->data->stop || ft_strncmp(status, PHILO_DIE, 30) == 0)
		printf("%-7ld %d : %s\n",
			   get_time_in_ms() - philo->data->start_t,
			   philo->id + 1, status);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
