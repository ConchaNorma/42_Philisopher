/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:07:05 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/11 22:12:38 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi_short(const char *str)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + ((int)*str - '0');
		if (num > 2147483647)
			return (-1);
		str++;
	}
	if (*str && (*str < '0' || *str > '9'))
		return (-1);
	return (num);
}

long	get_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (0);
}

int	check_arg(int argc, char **arg)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (-1);
	while (++i < argc)
	{
		if (ft_atoi_short(arg[i]) < 0)
			return (-1);
	}
	return (0);
}

void	wait_time(int wait_time)
{
	long	st;

	st = get_ms();
	while (get_ms() - st < wait_time)
		usleep(100);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i <= data->input->philos_num)
	{
		if (data->forks[i])
			free(data->forks[i]);
	}
	if (data->forks)
		free(data->forks);
	if (data->input)
		free(data->input);
	if (data->philo)
		free(data->philo);
	if (data->thread)
		free(data->thread);
	if (data)
		free(data);
}
