/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:35:08 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/22 12:35:21 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int ft_atoi(char *str)
{
	int res;
	int i;
	int sign;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int is_numeric_args(char **av)
{
	int i;
	int j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
			if (!is_digit(av[i][j++]))
				return (0);
		i++;
	}
	return (1);
}

int init_philosophers(t_data *data)
{
	int i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (printf("%s\n", ERR_MALLOC), 0);
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = 0;
		i++;
// init thread mais quand j aurais compris comment ca marche
	}
	return (1);
}

int init_data(t_data *data, char **av)
{
	if (!is_numeric_args(av + 1))
		return (printf("%s\n", ERR_ARGS_TYPE), 0);
	data->philo_count = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals_count = ft_atoi(av[5]);
	else
		data->meals_count = -1;
	if (!init_philosophers(data))
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_data data;

	if (ac != 5 && ac != 6)
		return (printf("%s\n", ERR_ARGS_COUNT));
	if (!init_data(&data, av))
		return (0);
	return (0);
}
