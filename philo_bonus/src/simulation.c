/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:07:05 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/16 18:52:17 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	ph_sleeping(t_data *data)
{
	sem_wait(data->print);
	printf("%ld ms %d is sleeping\n", get_ms() - data->start_time,
		data->philo_id);
	sem_post(data->print);
	wait_time (data->time_to_sleep);
	sem_wait(data->print);
	printf("%ld ms %d is thinking\n", get_ms() - data->start_time,
		data->philo_id);
	sem_post(data->print);
}

void	ph_eating(t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
	sem_wait(data->print);
	printf("%ld ms %d has taken fork\n", get_ms() - data->start_time,
		data->philo_id);
	printf("%ld ms %d has taken fork\n", get_ms() - data->start_time,
		data->philo_id);
	printf("%ld ms %d is eating\n", get_ms() - data->start_time,
		data->philo_id);
	sem_post(data->print);
	data->start_eat = get_ms();
	wait_time (data->time_to_eat);
	if (data->must_to_eat > 0)
		data->must_to_eat--;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	*death_check(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->philo_id == 0)
	{
		sem_wait(data->finish);
		data->death_status = 1;
		return (NULL);
	}
	while (data->death_status == 0)
	{
		if (data->must_to_eat == 0)
			exit(0);
		if ((get_ms() - data->start_eat) > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%ld ms %d is died\n", (get_ms() - data->start_time),
				data->philo_id);
			data->death_status = 1;
			sem_post(data->finish);
			exit(0);
		}
		usleep(500);
	}
	return (NULL);
}

void	*child_create(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	pthread_create(&data->thread, NULL, death_check, arg);
	pthread_detach(data->thread);
	i = 0;
	while (data->death_status == 0 && data->must_to_eat != 0)
	{
		if (i == 0 && ((data->philo_id == 1 && \
					(data->philos_num % 2)) || !(data->philo_id % 2)))
			i += 1;
		else
			ph_eating(data);
		ph_sleeping(data);
	}
	return (NULL);
}

int	simulation(t_data *data)
{
	int			i;

	i = -1;
	data->start_time = get_ms();
	data->start_eat = get_ms();
	while (++i < data->philos_num)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (printf("Error: fork creation\n"));
		if (data->pid[i] == 0)
		{
			data->philo_id = i + 1;
			child_create(data);
			return (0);
		}
	}
	pthread_create(&data->thread, NULL, death_check, data);
	pthread_detach(data->thread);
	return (0);
}
