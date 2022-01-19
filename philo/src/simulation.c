/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:07:05 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/16 19:17:48 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ph_sleeping(t_philo *philo)
{
	if (philo->data->death_status == 1)
		return ;
	pthread_mutex_lock(philo->print);
	printf("%ld ms %d is sleeping\n", get_ms() - philo->data->start_time,
		philo->philo_id);
	pthread_mutex_unlock(philo->print);
	wait_time (philo->input->time_to_sleep);
	if (philo->data->death_status == 1)
		return ;
	pthread_mutex_lock(philo->print);
	printf("%ld ms %d is thinking\n", get_ms() - philo->data->start_time,
		philo->philo_id);
	pthread_mutex_unlock(philo->print);
}

void	eat_counting(t_philo *philo)
{
	philo->start_eat = get_ms();
	wait_time (philo->input->time_to_eat);
	if (philo->ph_must_to_eat > 0)
		philo->ph_must_to_eat--;
	if (philo->ph_must_to_eat == 0)
		philo->data->finish_eat_flag++;
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	ph_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (philo->data->death_status == 1)
	{
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	pthread_mutex_lock(philo->print);
	printf("%ld ms %d has taken fork\n", get_ms() - philo->data->start_time,
		philo->philo_id);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->fork_right);
	if (philo->data->death_status == 1)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	pthread_mutex_lock(philo->print);
	printf("%ld ms %d has taken fork\n", get_ms() - philo->data->start_time,
		philo->philo_id);
	printf("%ld ms %d is eating\n", get_ms() - philo->data->start_time,
		philo->philo_id);
	pthread_mutex_unlock(philo->print);
	eat_counting(philo);
}

void	*thread_create(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (philo->data->death_status == 0 && philo->ph_must_to_eat != 0)
	{
		if (i == 0 && ((philo->philo_id == 1 && \
					(philo->input->philos_num % 2)) || !(philo->philo_id % 2)))
			i += 1;
		else
			ph_eating(philo);
		ph_sleeping(philo);
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	int			i;
	static int	j = 0;

	i = -1;
	data->start_time = get_ms();
	while (++i < data->input->philos_num)
	{
		pthread_create(&data->thread[i], NULL, thread_create, &data->philo[i]);
		pthread_detach(data->thread[i]);
	}
	while (data->finish_eat_flag < data->input->philos_num
		&& data->death_status == 0)
	{
		if ((get_ms() - data->philo[j].start_eat) > data->input->time_to_die
			&& data->philo[j].ph_must_to_eat != 0)
		{
			pthread_mutex_lock(data->philo[j].print);
			printf("%ld ms %d is died\n", (get_ms() - data->start_time),
				data->philo[j].philo_id);
			data->death_status = 1;
			pthread_mutex_unlock(data->philo[j].print);
			break ;
		}
		j = (j + 1) % data->input->philos_num;
	}
}
