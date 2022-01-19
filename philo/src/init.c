/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:07:05 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/16 15:39:40 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t)
			* (data->input->philos_num + 1));
	if (!data->forks)
		return (printf("forks: malloc error\n"));
	while (++i <= data->input->philos_num)
	{
		data->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i])
			return (printf("forks: malloc error\n"));
		if (pthread_mutex_init(data->forks[i], NULL) != 0)
			return (printf("forks: init error\n"));
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->thread = (pthread_t *)malloc(sizeof(pthread_t)
			* data->input->philos_num);
	data->philo = (t_philo *)malloc(sizeof(t_philo)
			* data->input->philos_num);
	if (!data->thread || !data->philo)
		return (printf("philo: malloc error\n"));
	while (++i < data->input->philos_num)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].ph_must_to_eat = data->input->must_to_eat;
		data->philo[i].input = data->input;
		data->philo[i].data = data;
		data->philo[i].start_eat = get_ms();
		data->philo[i].fork_left = data->forks[i];
		data->philo[i].fork_right
			= data->forks[(i - 1 + data->input->philos_num)
			% data->input->philos_num];
		data->philo[i].print = data->forks[data->input->philos_num];
	}
	return (0);
}

int	init_data(t_data *data, char **arg)
{
	data->input = (t_input *)malloc(sizeof(t_input));
	if (!data->input)
		return (printf("malloc error\n"));
	data->input->philos_num = ft_atoi_short(arg[1]);
	data->input->time_to_die = ft_atoi_short(arg[2]);
	data->input->time_to_eat = ft_atoi_short(arg[3]);
	data->input->time_to_sleep = ft_atoi_short(arg[4]);
	if (arg[5])
		data->input->must_to_eat = ft_atoi_short(arg[5]);
	else
		data->input->must_to_eat = -1;
	data->death_status = 0;
	data->finish_eat_flag = 0;
	if (data->input->time_to_die <= (data->input->time_to_eat
			+ data->input->time_to_sleep) || data->input->must_to_eat == 0)
		return (printf("Incorrect arguments\n"));
	if (init_forks(data) != 0 || init_philos(data) != 0)
		return (1);
	return (0);
}
