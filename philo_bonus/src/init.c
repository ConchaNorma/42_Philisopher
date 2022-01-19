/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:07:05 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/16 18:55:17 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	init_sem(t_data *data)
{
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->philos_num);
	if (data->forks == SEM_FAILED)
		return (printf("forks: sem_open error\n"));
	sem_unlink("/print");
	data->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	if (data->print == SEM_FAILED)
		return (printf("print: sem_open error\n"));
	sem_unlink("/finish");
	data->finish = sem_open("/finish", O_CREAT, S_IRWXU, 0);
	if (data->finish == SEM_FAILED)
		return (printf("finish: sem_open error\n"));
	return (0);
}

int	init_data(t_data *data, char **arg)
{
	data->pid = NULL;
	data->philos_num = ft_atoi_short(arg[1]);
	data->time_to_die = ft_atoi_short(arg[2]);
	data->time_to_eat = ft_atoi_short(arg[3]);
	data->time_to_sleep = ft_atoi_short(arg[4]);
	if (arg[5])
		data->must_to_eat = ft_atoi_short(arg[5]);
	else
		data->must_to_eat = -1;
	data->death_status = 0;
	data->philo_id = 0;
	if (data->time_to_die <= (data->time_to_eat
			+ data->time_to_sleep) || data->must_to_eat == 0)
		return (printf("Error: Incorrect arguments\n"));
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->philos_num);
	if (!data->pid)
		return (printf("philo_pid: malloc error\n"));
	if (init_sem(data) != 0)
		return (printf("Error: malloc error for semaphors\n"));
	return (0);
}
