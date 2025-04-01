/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:43:10 by jbastard          #+#    #+#             */
/*   Updated: 2025/03/25 14:55:24 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/philosophers.h"

int is_digit(int c)
{
	return (c >= '0' && c <= '9');
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

int ft_atoi(const char *str)
{
	int res;
	int i;
	int sign;

	i = 0;
	sign = 1;
	res = 0;
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

long int ft_atol(const char *str)
{
	int res;
	int i;
	int sign;

	i = 0;
	sign = 1;
	res = 0;
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