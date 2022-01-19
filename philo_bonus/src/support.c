/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:07:05 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/16 18:51:22 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
		usleep(500);
}

void	free_data(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/finish");
	if (data->pid)
		free(data->pid);
	if (data)
		free(data);
}
