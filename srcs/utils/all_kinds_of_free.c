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

void	free_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	free(data->philos);
}
